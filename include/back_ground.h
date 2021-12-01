#ifndef RAYCAST_BACK_GROUND_H
#define RAYCAST_BACK_GROUND_H
// private headers
#include "config.h"

struct BackGround {
    size_t img_w;
    size_t img_h;
    std::vector<Pixel> back_ground; // Хранилище текстур

    BackGround(const std::string filename, const Pixel format);
    [[nodiscard]] Pixel get(const size_t i, size_t j) const; // Получаем пиксель
};
#endif //RAYCAST_BACK_GROUND_H
