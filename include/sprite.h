#ifndef SPRITE_H
#define SPRITE_H
// c++ headers
#include <iostream>

struct Sprite {
    float x;
    float y;
    size_t tex_id;
    float player_dist;
    bool operator < (const Sprite& s) const;
};



#endif // SPRITE_H