#ifndef RAYCAST_DRAW_FON_BUTTON_H
#define RAYCAST_DRAW_FON_BUTTON_H
// private headers
#include "button.h"

// c++ headers
#include <string>

struct DrawFonButton{
    DrawFonButton(const std::string& b_s, const std::string& f_s);
    ~DrawFonButton();

    void draw_static(SDL_Renderer* renderer);

    SDL_Surface* button_skin;
    SDL_Surface* fon_skin;
};

#endif //RAYCAST_DRAW_FON_BUTTON_H
