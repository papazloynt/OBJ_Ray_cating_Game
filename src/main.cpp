#define _USE_MATH_DEFINES
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>

#include <sstream>
#include <iomanip>

#include "../include/map.h"
#include "../include/ppm_utils.h"
#include "../include/player.h"
#include "../include/sprite.h"
#include "../include/gamewindow.h"
#include "../include/textures.h"

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

void map_show_sprite(Sprite &sprite, GameWindow &gw, Map &map) {
    const size_t rect_w = gw.w / (map.w * 2); // Размер ячейки одной ячейки карты
    const size_t rect_h = gw.h / map.h;
    gw.draw_rectangle(sprite.x * rect_w - 3, sprite.y * rect_h - 3, 6, 6, ppm::pack_color(255, 0, 0)); // Вычитаем 3, т.к. нужно получить левый угол квадратика
}

void draw_sprite(Sprite &sprite, std::vector<float> &depth_buffer, GameWindow &gw, Player &player, WallTexture &tex_sprites) {
    // Вычесления для того, чтобы центр спрайта смотрел на главного персонажа
    float sprite_dir = atan2(sprite.y - player.y, sprite.x - player.x);
    while (sprite_dir - player.a >  M_PI) sprite_dir -= 2*M_PI; // Чтобы спрайт не смотрел в противоположную сторону, убираем периоды
    while (sprite_dir - player.a < -M_PI) sprite_dir += 2*M_PI;

    size_t sprite_screen_size = std::min(1000, static_cast<int>(gw.h/sprite.player_dist)); // Размер спрайта ограничим 1000
    int h_offset = (sprite_dir - player.a)/player.fov*(gw.w/2) + (gw.w/2)/2 - tex_sprites.size/2; // т.к. экран на половине
    int v_offset = gw.h/2 - sprite_screen_size/2;

    for (int i=0; i<sprite_screen_size; ++i) {
        if (h_offset+i<0 || h_offset+i>=gw.w/2) continue;
        if (depth_buffer[h_offset+i]<sprite.player_dist) continue; // Столбец спрайта закрыт стеной, не рисуем.
        for (int j=0; j<sprite_screen_size; ++j) {
            if (v_offset+j<0 || v_offset+j>=gw.h) continue;
            uint32_t color = tex_sprites.get(i*tex_sprites.size/sprite_screen_size, j*tex_sprites.size/sprite_screen_size, sprite.tex_id);
            uint8_t r,g,b,a;
            ppm::unpack_color(color, r, g, b, a);
            if (a>128)
            gw.set_pixel(gw.w/2 + h_offset+i, v_offset+j, ppm::pack_color(0,0,0));
        }
    }
}











void render(GameWindow &gw, Map &map, Player &player, std::vector<Sprite> &sprites, WallTexture &tex_walls, WallTexture &tex_pers) {
    gw.clear(ppm::pack_color(255, 255, 255));
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

    std::vector<float> depth_buffer(gw.w/2, 1e3);
    for (size_t i=0; i<gw.w/2; i++) { // рисуем видимую область
        float angle = player.a-player.fov/2 + player.fov*i/float(gw.w/2);
        for (float t=0; t<20; t+=.01) { // размер луча
            float x = player.x + t*cos(angle);
            float y = player.y + t*sin(angle);
            gw.set_pixel(x*rect_w, y*rect_h, ppm::pack_color(160, 160, 160)); // Луч видимости на карте

            if (map.is_empty(x, y)) continue;

            size_t texid = map.get(x, y);
            assert(texid<tex_walls.count);
            float dist = t*cos(angle-player.a);
            depth_buffer[i] = dist;
            size_t column_height = gw.h/dist;
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
    //Костыль, но он работает.
    for (size_t i=0; i<sprites.size(); ++i) { // Обновляем расстояние от игрока до каждого спрайта
        sprites[i].player_dist = std::sqrt(pow(player.x - sprites[i].x, 2) + pow(player.y - sprites[i].y, 2));
    }
    std::sort(sprites.begin(), sprites.end()); // Сортируем их от дальних, к ближним

    for (size_t i=0; i < sprites.size(); ++i) {
        map_show_sprite(sprites[i], gw, map);
        draw_sprite(sprites[i], depth_buffer, gw, player, tex_pers);
    }
}

// сущность алгоритмы

int main() {
    GameWindow gw{1024, 512, std::vector<uint32_t>(1024*512, ppm::pack_color(255, 255, 255))};
    Player player{3.456, 2.345, 1.523, M_PI/3.};
    Map map;

    WallTexture tex_walls("../img/walltext.png");
    WallTexture tex_monst("../img/black.png");

    if (!tex_walls.count) {
        std::cerr << "Failed to load textures" << std::endl;
        return -1;
    }
    std::vector<Sprite> sprites{ {3.523, 3.812, 2, 0}, {1.834, 8.765, 0, 0}, {5.323, 5.365, 1, 0}, {4.123, 10.265, 1, 0} };

    for (size_t frame=0; frame<360; frame++) {
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(5) << frame << ".ppm";
        player.a += 2*M_PI/360;
        render(gw, map, player, sprites, tex_walls, tex_monst);
        ppm::create_ppm_image(ss.str(), gw.img, gw.w, gw.h);
    }

    return 0;
}