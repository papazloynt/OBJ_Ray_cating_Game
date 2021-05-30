// private headers
#include "spite_drawing.h"

// c++ headers
#include <cmath>

SpriteDrawing::SpriteDrawing(const Sprite& s) : sprite(s) {}

void SpriteDrawing::map_show_sprite(GameWindow &gw, Map &map) {
    const size_t rect_w = gw.w / (map.w * 2); // Размер одной ячейки карты
    const size_t rect_h = gw.h / map.h;
    gw.draw_rectangle(sprite.x * rect_w - 3, sprite.y * rect_h - 3, 6, 6, ppm::pack_color(255, 0, 0)); // Вычитаем 3, т.к. нужно получить левый угол квадратика
}

void SpriteDrawing::draw_sprite(std::vector<float> &depth_buffer, GameWindow &gw, Player &player, WallTexture &tex_sprites) {
    // Вычесления для того, чтобы центр спрайта смотрел на главного персонажа
    float sprite_dir = atan2(sprite.y - player.y, sprite.x - player.x);
    while (sprite_dir - player.a >  M_PI) sprite_dir -= 2*M_PI; // Чтобы спрайт не смотрел в противоположную сторону, убираем периоды
    while (sprite_dir - player.a < -M_PI) sprite_dir += 2*M_PI;

    size_t sprite_screen_size = std::min(2000, static_cast<int>(gw.h/sprite.player_dist)); // Размер спрайта ограничим 2000
    int h_offset = (sprite_dir - player.a)*(gw.w/2)/(player.fov) + (gw.w/2)/2 - tex_sprites.size/2; // т.к. экран на половине
    int v_offset = gw.h/2 - sprite_screen_size/2;

    for (size_t i=0; i < sprite_screen_size; ++i) {
        if (h_offset + int(i) < 0 || h_offset + i >= gw.w/2) continue;
        if (depth_buffer[h_offset+i] < sprite.player_dist) continue; // Столбец спрайта закрыт стеной, не рисуем.
        for (size_t j = 0; j < sprite_screen_size; ++j) {
            if (v_offset + int(j) < 0 || v_offset + j >= gw.h) continue;
            uint32_t color = tex_sprites.get(i*tex_sprites.size/sprite_screen_size, j*tex_sprites.size/sprite_screen_size, sprite.tex_id);
            uint8_t r,g,b,a;
            ppm::unpack_color(color, r, g, b, a);
            if (a>128)
                gw.set_pixel(gw.w/2 + h_offset+i, v_offset+j, color);
        }
    }
}

bool SpriteDrawing::operator < (const SpriteDrawing& s) const {
    return sprite.player_dist > s.sprite.player_dist;
}