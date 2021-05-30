// private headers
#include "map_drawing.h"

// c++ headers
#include <cassert>

void MapDrawing::Draw(GameWindow &gw, Map &map, WallTexture &tex_walls) {
    rect_w = gw.w / (map.w * 2);
    rect_h = gw.h / map.h;
    for (size_t j = 0; j < map.h; ++j) {  // Рисуем карту
        for (size_t i = 0; i < map.w; ++i) {
            if (map.is_empty(i, j)) continue; // Пропускаем, если пробел
            size_t rect_x = i * rect_w;
            size_t rect_y = j * rect_h;
            size_t texid = map.get(i, j);
            assert(texid < tex_walls.count);
            gw.draw_rectangle(rect_x, rect_y, rect_w, rect_h, tex_walls.get(0, 0, texid)); // Верхний пиксель текстуры
        }
    }
}
