// private headers
#include "render.h"

// c++ headers
#include <algorithm>

void render(GameWindow &gw, Map &map, Player &player, std::vector<SpriteDrawing> &sprites, WallTexture &tex_walls, WallTexture &tex_pers) {
    gw.clear(ppm::pack_color(255, 255, 255));
    MapDrawing md;
    md.Draw(gw, map, tex_walls);

    std::vector<float> depth_buffer(gw.w/2, 1e3);
    Walls::ray_cast(gw, map, player, tex_walls, depth_buffer, md.rect_w, md.rect_h, tex_walls.size);

    //Костыль, но он работает.
    for (size_t i = 0; i < sprites.size(); ++i) { // Обновляем расстояние от игрока до каждого спрайта
        sprites[i].sprite.player_dist = std::sqrt(pow(player.x - sprites[i].sprite.x, 2) + pow(player.y - sprites[i].sprite.y, 2));
    }
    std::sort(sprites.begin(), sprites.end()); // Сортируем их от дальних, к ближним

    for (size_t i = 0; i < sprites.size(); ++i) {
        sprites[i].map_show_sprite(gw, map);
        sprites[i].draw_sprite(depth_buffer, gw, player, tex_pers);
    }
}