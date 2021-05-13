#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>

#include <sstream>
#include <iomanip>

#include "example/Map.h"
#include "example/utils.h"
#include "example/Player.h"
#include "example/sprite.h"
#include "example/framebuffer.h"
#include "example/textures.h"


int wall_x_texcoord(const float x, const float y, WallTexture &tex_walls) {
    float hitx = x - floor(x+.5);
    float hity = y - floor(y+.5);
    int tex = hitx*tex_walls.size;
    if (std::abs(hity)>std::abs(hitx))
        tex = hity*tex_walls.size;
    if (tex<0) // Если отрицательное, то обрабатываем этот случай
        tex += tex_walls.size;
    assert(tex>=0 && tex<(int)tex_walls.size);
    return tex;
}


void render(GameWindow &gw, Map &map, Player &player, Texture &tex_walls) {
    gw.clear(pack_color(255, 255, 255));
    const size_t rect_w = gw.w/(map.w*2);
    const size_t rect_h = gw.h/map.h;
    for (size_t j=0; j<map.h; j++) {  // Рисуем карту
        for (size_t i=0; i<map.w; i++) {
            if (map.is_empty(i, j)) continue; // Пропускаем, если пробел
            size_t rect_x = i*rect_w;
            size_t rect_y = j*rect_h;
            size_t texid = map.get(i, j);
            assert(texid<tex_walls.count);
            gw.draw_rectangle(rect_x, rect_y, rect_w, rect_h, tex_walls.get(0, 0, texid)); // Верхний пиксель текстуры
        }
    }

    for (size_t i=0; i<gw.w/2; i++) { // рисуем видимую область
        float angle = player.a-player.fov/2 + player.fov*i/float(gw.w/2);
        for (float t=0; t<20; t+=.01) { // размер луча
            float x = player.x + t*cos(angle);
            float y = player.y + t*sin(angle);
            gw.set_pixel(x*rect_w, y*rect_h, pack_color(160, 160, 160)); // Видимые стены

            if (map.is_empty(x, y)) continue;

            size_t texid = map.get(x, y);
            assert(texid<tex_walls.count);
            size_t column_height = gw.h/(t*cos(angle-player.a));
            int x_texcoord = wall_x_texcoord(x, y, tex_walls);
            std::vector<uint32_t> column = tex_walls.get_scaled_column(texid, x_texcoord, column_height);
            int pix_x = i + gw.w/2;

            for (size_t j=0; j<column_height; j++) {
                int pix_y = j + gw.h/2 - column_height/2;
                if (pix_y>=0 && pix_y<(int)gw.h) {
                    gw.set_pixel(pix_x, pix_y, column[j]);
                }
            }
            break;
        }
    }
}





int main() {
    GameWindow gw{1024, 512, std::vector<uint32_t>(1024*512, pack_color(255, 255, 255))};
    Player player{3.456, 2.345, 1.523, M_PI/3.};
    Map map;

    WallTexture tex_walls("../img/walltext.png");
    if (!tex_walls.count) {
        std::cerr << "Failed to load wall textures" << std::endl;
        return -1;
    }

    for (size_t frame=0; frame<360; frame++) {
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(5) << frame << ".ppm";
        player.a += 2*M_PI/360;
        render(gw, map, player, tex_walls);
        drop_ppm_image(ss.str(), gw.img, gw.w, gw.h);
    }

    return 0;
}