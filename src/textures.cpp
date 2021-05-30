// private headers
#include "ppm_utils.h"
#include "textures.h"

// c++ headers
#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>

// SDL
#include "SDL.h"

WallTexture::WallTexture(const std::string filename, const Pixel format) : img_w(0), img_h(0), count(0), size(0), tex_counter() {
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
    count = w/h;
    size = w/count;
    img_w = w;
    img_h = h;
    uint8_t *pixmap = reinterpret_cast<uint8_t *>(surface->pixels);

    tex_counter = std::vector<Pixel>(w*h);
    for (int j=0; j<h; j++) {
        for (int i=0; i<w; i++) {
            uint8_t r = pixmap[(i+j*w)*4+0];
            uint8_t g = pixmap[(i+j*w)*4+1];
            uint8_t b = pixmap[(i+j*w)*4+2];
            uint8_t a = pixmap[(i+j*w)*4+3];
            tex_counter[i+j*w] = ppm::pack_color(r, g, b, a);
        }
    }
    SDL_FreeSurface(surface);
}

Pixel WallTexture::get(const size_t i, const size_t j, const size_t idx) const {
    return tex_counter[i+idx*size+j*img_w];
}

std::vector<Pixel> WallTexture::get_scaled_column(const size_t texture_id, const size_t tex_coord, const size_t column_height) const {
    assert(tex_coord<size && texture_id<count);
    std::vector<Pixel> column(column_height);
    for (size_t y=0; y<column_height; y++) {
        column[y] = get(tex_coord, (y*size)/column_height, texture_id);
    }
    return column;
}