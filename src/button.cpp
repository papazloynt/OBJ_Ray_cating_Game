// private headers
#include "button.h"

Button::Button(SDL_Surface* s, SDL_Rect d_r, Colour_ c) :
                        skin(s), draw_rect(d_r), pressed(false), colour(c) {}

void Button::button_process_event(const SDL_Event *ev) {
    if(ev->type == SDL_MOUSEBUTTONDOWN) {
        if(ev->button.button == SDL_BUTTON_LEFT &&
           ev->button.x >=draw_rect.x &&
           ev->button.x <= (draw_rect.x + draw_rect.w) &&
           ev->button.y >= draw_rect.y &&
           ev->button.y <= (draw_rect.y + draw_rect.h)) {
            pressed = true;
        }
    }
}

void Button::button_drawing(SDL_Renderer *r) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(r, skin);

    SDL_SetRenderDrawColor(r, colour.r, colour.g, colour.b, colour.a);
    SDL_RenderFillRect(r, &draw_rect);

    SDL_RenderCopy(r, texture, NULL, &draw_rect);
    if(pressed) pressed = false;
}
