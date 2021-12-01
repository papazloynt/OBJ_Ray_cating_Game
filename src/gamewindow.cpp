// private headers
#include "gamewindow.h"

// c++ headers
#include <vector>
#include <cassert>

GameWindow::GameWindow(size_t _w, size_t _h, std::vector<Pixel> _img) : w(_w), h(_h), img(_img) {}

void GameWindow::set_pixel(const size_t x, const size_t y, const Pixel color) {
    assert(img.size()==w*h && x<w && y<h);
    img[x+y*w] = color;
}

void GameWindow::draw_rectangle(const size_t rect_x, const size_t rect_y, const size_t rect_w, const size_t rect_h, const Pixel color) {
    assert(img.size()==w*h);
    for (size_t i=0; i<rect_w; i++) {
        for (size_t j=0; j<rect_h; j++) {
            size_t cx = rect_x+i;
            size_t cy = rect_y+j;
            if (cx<w && cy<h)
                set_pixel(cx, cy, color);
        }
    }
}

void GameWindow::clear(const Pixel color) {
    std::fill(img.begin(), img.end(), color);
}
