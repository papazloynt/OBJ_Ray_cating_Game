#ifndef RAYCAST_BUTTON_H
#define RAYCAST_BUTTON_H
// c++ headers
#include "iostream"

// SDL
#include "SDL.h"

struct Colour_ {
    uint8_t r, g, b, a;
};

struct Button {
    Button(SDL_Surface* s, SDL_Rect d_r, Colour_ c);
    void button_process_event(const SDL_Event *ev);
    void button_drawing(SDL_Renderer *r);

    SDL_Surface* skin;
    SDL_Rect draw_rect;
    bool pressed;
    Colour_ colour;
};

#endif //RAYCAST_BUTTON_H
