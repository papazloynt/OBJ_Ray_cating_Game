#ifndef RAYCAST_ALGORITHMS_H
#define RAYCAST_ALGORITHMS_H
// private headers
#include <gamewindow.h>
#include "map.h"
#include "player.h"
#include "ppm_utils.h"
#include "textures.h"
#include "back_ground.h"

// c++ headers
#include <iostream>
#include <cmath>

namespace Walls{
    // Считает ширину колонны текстуры
    int wall_width_texture_coord(const float x, const float y, const int size);

    void ray_cast(GameWindow &gw, Map &map, Player &player, WallTexture &tex_walls,
                  std::vector<float>& d_b, const size_t rect_w, const size_t rect_h, const int size);
}

#endif //RAYCAST_ALGORITHMS_H
