#ifndef TEXTURES_H
#define TEXTURES_H
// private headers
#include "config.h"

struct WallTexture {
    size_t img_w;
    size_t img_h;
    size_t count;
    size_t size;
    std::vector<Pixel> tex_counter; // Хранилище текстур

    WallTexture(const std::string filename, const Pixel format);
    [[nodiscard]] Pixel get(const size_t i, size_t j, const size_t idx) const; // Получаем пиксель
    std::vector<Pixel> get_scaled_column(const size_t texture_id, const size_t tex_coord, const size_t column_height) const; // Поулчаем колонну текстуры
};

#endif // TEXTURES_H