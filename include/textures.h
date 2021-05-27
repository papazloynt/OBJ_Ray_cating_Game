#ifndef TEXTURES_H
#define TEXTURES_H

struct WallTexture {
    size_t img_w;
    size_t img_h;
    size_t count, size;  // число текстур и размер их в пикселях
    std::vector<uint32_t> img; // Хранилище текстур

    WallTexture(const std::string filename);
    uint32_t& get(const size_t i, const size_t j, const size_t idx); // Получаем пиксель
    std::vector<uint32_t> get_scaled_column(const size_t texture_id, const size_t tex_coord, const size_t column_height); // Поулчаем колонну текстуры
};

#endif // TEXTURES_H