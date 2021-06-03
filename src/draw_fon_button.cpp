//private headers
#include "draw_fon_button.h"

DrawFonButton::DrawFonButton(const std::string& b_s, const std::string& f_s) :
                                        button_skin(SDL_LoadBMP(b_s.c_str())),
                                        fon_skin(SDL_LoadBMP(f_s.c_str())) {}
DrawFonButton::~DrawFonButton() {
        SDL_FreeSurface(button_skin);
        SDL_FreeSurface(fon_skin);
}

void DrawFonButton::draw_static(SDL_Renderer* renderer){
    Button button{ button_skin , { 450, 240, 128, 50 } , { 255, 255, 255, 255} };
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, fon_skin);
    SDL_RenderClear(renderer);

    SDL_Event evt;
    while(true) {
        if (SDL_PollEvent(&evt)) {
            if(evt.type == SDL_QUIT ||
               (evt.type == SDL_WINDOWEVENT && evt.window.event == SDL_WINDOWEVENT_CLOSE) ||
               (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE)) {
                break;
            }
            button.button_process_event(&evt);
        }
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        if(!button.pressed) {
            button.button_drawing(renderer);
        } else {
            SDL_RenderClear(renderer);
            break;
        }
        SDL_RenderPresent(renderer);
    }
}
