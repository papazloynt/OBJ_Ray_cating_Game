#ifndef RAYCAST_MAP_DRAWING_H
#define RAYCAST_MAP_DRAWING_H
// private headers
#include "gamewindow.h"
#include "map.h"
#include "textures.h"



struct MapDrawing{
    size_t rect_w = 0;
    size_t rect_h = 0;
    void Draw(GameWindow &gw, Map &map, WallTexture &tex_walls);
};




#endif //RAYCAST_MAP_DRAWING_H
