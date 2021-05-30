#ifndef RAYCAST_ALGORITHMS_H
#define RAYCAST_ALGORITHMS_H


namespace Walls{
    // Считает ширину колонны текстуры
    int wall_width_texture_coord(const float x, const float y, WallTexture &tex_walls) {
        float hitx = x - floor(x+.5);
        float hity = y - floor(y+.5);
        int tex = hitx * tex_walls.size;
        if (std::abs(hity) > std::abs(hitx))
            tex = hity * tex_walls.size;
        if (tex < 0) // Если отрицательное, то обрабатываем этот случай
            tex += tex_walls.size;
        assert(tex >= 0 && tex< (int)tex_walls.size);
        return tex;
    }
}

namespace SpriteLogic{

}

namespace PlayerLogic{

}

#endif //RAYCAST_ALGORITHMS_H
