#ifndef RAYCAST_SPITE_DRAWING_H
#define RAYCAST_SPITE_DRAWING_H
// private headers
#include "sprite.h"
#include "gamewindow.h"
#include "map.h"
#include "player.h"
#include "textures.h"
#include "ppm_utils.h"

struct SpriteDrawing{
    SpriteDrawing(const Sprite& s);

    Sprite sprite;
    void map_show_sprite(GameWindow &gw, Map &map);
    void draw_sprite(std::vector<float> &depth_buffer, GameWindow &gw, Player &player, WallTexture &tex_sprites);

    bool operator < (const SpriteDrawing& s) const;
};






#endif //RAYCAST_SPITE_DRAWING_H
