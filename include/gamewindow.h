#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
// private headers
#include "config.h"

// c++ headers
#include <iostream>
#include <vector>

struct GameWindow {
    size_t w;
    size_t h;
    std::vector<uint32_t> img;

    GameWindow(size_t _w, size_t _h, std::vector<Pixel> _img);
    ~GameWindow() = default;

    void clear(const Pixel color);
    void set_pixel(const size_t x, const size_t y, const Pixel color);
    void draw_rectangle(const size_t x, const size_t y, const size_t w, const size_t h, const Pixel color);
};

#endif // FRAMEBUFFER_H