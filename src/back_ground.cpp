// private headers
#include "ppm_utils.h"
#include "back_ground.h"

// c++ headers
#include <vector>
#include <cstdint>
#include <cassert>

// SDL
#include "SDL.h"

BackGround::BackGround(const std::string filename, const Pixel format) {
    SDL_Surface *tmp = SDL_LoadBMP(filename.c_str());
    if (!tmp) {
        std::cerr << "Error in SDL_LoadBMP: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Surface *surface = SDL_ConvertSurfaceFormat(tmp, format, 0);
    SDL_FreeSurface(tmp);
    if (!surface) {
        std::cerr << "Error in SDL_ConvertSurfaceFormat: " << SDL_GetError() << std::endl;
        return;
    }

    int w = surface->w;
    int h = surface->h;

    if (w!=h*int(w/h)) {
        std::cerr << "Error: the texture file must contain N square textures packed horizontally" << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    img_w = w;
    img_h = h;
    uint8_t *pixmap = reinterpret_cast<uint8_t *>(surface->pixels);

    back_ground = std::vector<Pixel>(w*h);
    for (int j=0; j<h; j++) {
        for (int i=0; i<w; i++) {
            uint8_t r = pixmap[(i+j*w)*4+0];
            uint8_t g = pixmap[(i+j*w)*4+1];
            uint8_t b = pixmap[(i+j*w)*4+2];
            uint8_t a = pixmap[(i+j*w)*4+3];
            back_ground[i+j*w] = ppm::pack_color(r, g, b, a);
        }
    }
    SDL_FreeSurface(surface);
}

Pixel BackGround::get(const size_t i, const size_t j) const {
    return back_ground[i+j*img_w];
}