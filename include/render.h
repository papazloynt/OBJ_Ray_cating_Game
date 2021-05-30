#ifndef RAYCAST_RENDER_H
#define RAYCAST_RENDER_H
// private headers
#include "config.h"
#include "spite_drawing.h"
#include "algorithms.h"
#include "map_drawing.h"

void render(GameWindow &gw, Map &map, Player &player, std::vector<SpriteDrawing> &sprites, WallTexture &tex_walls, WallTexture &tex_pers);
#endif //RAYCAST_RENDER_H
