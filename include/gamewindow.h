#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <cstdlib>
#include <vector>

struct GameWindow {
    size_t w;
    size_t h;
    std::vector<uint32_t> img;

    GameWindow(size_t _w, size_t _h, std::vector<uint32_t> _img);
    ~GameWindow() = default;

    void clear(const uint32_t color);
    void set_pixel(const size_t x, const size_t y, const uint32_t color);
    void draw_rectangle(const size_t x, const size_t y, const size_t w, const size_t h, const uint32_t color);
};

#endif // FRAMEBUFFER_H