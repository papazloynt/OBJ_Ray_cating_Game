// private headers
#include "ppm_utils.h"

namespace  ppm {
    Pixel pack_color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) {
        return (a << 24) + (b << 16) + (g << 8) + r;
    }

    [[maybe_unused]] void unpack_color(const uint32_t &color, uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a) {
        r = (color >> 0) & 255;
        g = (color >> 8) & 255;
        b = (color >> 16) & 255;
        a = (color >> 24) & 255;
    }
}