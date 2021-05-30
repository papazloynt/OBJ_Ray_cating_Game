// private headers
#include "algorithms.h"

// c++ headers
#include <cmath>
#include <cassert>

// sDL
#include "SDL.h"

int Walls::wall_width_texture_coord(const float x, const float y, const int size) {
    float hitx = x - floor(x+.5);
    float hity = y - floor(y+.5);
    int tex = hitx * size;
    if (std::abs(hity) > std::abs(hitx))
        tex = hity * size;
    if (tex < 0) // Если отрицательное, то обрабатываем этот случай
        tex += size;
    assert(tex >= 0 && tex< size);
    return tex;
}

void Walls::ray_cast(GameWindow &gw, Map &map, Player &player, WallTexture &tex_walls, std::vector<float>& d_b, const size_t rect_w, const size_t rect_h, const int size) {
    BackGround pol("../img/grey_1.bmp", SDL_PIXELFORMAT_ABGR8888);

/*
BackGround nebo("../img/grey_1.bmp", SDL_PIXELFORMAT_ABGR8888);
*/

    for (size_t i = 0; i < gw.w / 2; ++i) { // рисуем видимую область
        float angle = player.a - player.fov / 2 + player.fov * i / float(gw.w/2);
        for (float t = 0; t < 20; t += .01) { // размер луча
            float x = player.x + t*cos(angle);
            float y = player.y + t*sin(angle);
            gw.set_pixel(x*rect_w, y*rect_h, ppm::pack_color(160, 160, 160)); // Луч видимости на карте

            if (map.is_empty(x, y)) continue;

            size_t texid = map.get(x, y);

            float dist = 0.2 + t * cos(angle-player.a);
            d_b[i] = dist;
            size_t column_height = gw.h/dist;
            int x_texcoord = Walls::wall_width_texture_coord(x, y, size);

            std::vector<uint32_t> column = tex_walls.get_scaled_column(texid, x_texcoord, column_height);
            int pix_x = i + gw.w/2;

            // Тут отрисовка неба, пола и стен

            /*// небо
            for (size_t j = 0; j < gw.h/2 - column_height/2; j++) {
                    gw.set_pixel(pix_x, j, nebo.get(pix_x, j));
            }*/

            // Стены
            for (size_t j = 0; j < column_height; j++) {
                int pix_y = j + gw.h/2 - column_height/2;
                if (pix_y >= 0 && pix_y < (int)gw.h) {
                    gw.set_pixel(pix_x, pix_y, column[j]);
                }
            }

            for (size_t j = gw.h/2 + column_height/2; j < gw.h; j++) {
                    gw.set_pixel(pix_x, j, pol.get(pix_x, j));
            }

            break;
        }
    }
}