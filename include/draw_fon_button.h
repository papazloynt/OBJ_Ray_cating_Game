#ifndef RAYCAST_DRAW_FON_BUTTON_H
#define RAYCAST_DRAW_FON_BUTTON_H
// private headers
#include "button.h"

// c++ headers
#include <string>

enum Fon{
    Menu,
    Instraction
};


struct DrawFonButton{
    DrawFonButton(Fon fon_, const std::string& b_s, const std::string& f_s);
    ~DrawFonButton();

    void draw_static(SDL_Renderer* renderer);

    Fon fon;
    SDL_Surface* button_skin;
    SDL_Surface* fon_skin;
};

#endif //RAYCAST_DRAW_FON_BUTTON_H
