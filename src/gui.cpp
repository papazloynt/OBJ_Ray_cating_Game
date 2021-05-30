// private headers
#include "render.h"

// c++ headerswwwwwwwwww
#include <cmath>
#include <vector>

// SDL
#include "SDL.h"

int main() {
    GameWindow gw{1024, 512, std::vector<uint32_t>(1024*512, ppm::pack_color(255, 255, 255))};
    Player player{4.27, 2.345, 1.523, M_PI/3., 0, 0};
    Map map;

    WallTexture tex_walls("../img/walltext.bmp", SDL_PIXELFORMAT_ABGR8888);
    WallTexture tex_monst("../img/bicycle_1.bmp", SDL_PIXELFORMAT_ABGR8888);

    if (!tex_walls.count) {
        std::cerr << "Failed to load textures" << std::endl;
        return -1;
    }
    std::vector<SpriteDrawing> sprites{  Sprite{1.834, 8.765, 0, 0}, Sprite{5.323, 5.365, 1, 0}, Sprite{4.123, 10.265, 1, 0} };

    SDL_Window   *window   = nullptr;
    SDL_Renderer *renderer = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    if (SDL_CreateWindowAndRenderer(gw.w, gw.h, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS, &window, &renderer)) {
        std::cerr << "Couldn't create window and renderer: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Texture *framebuffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, gw.w, gw.h);

    SDL_Event event;
    while (true) {
        if (SDL_PollEvent(&event)) {
            if (SDL_QUIT==event.type || (SDL_KEYDOWN==event.type && SDLK_ESCAPE==event.key.keysym.sym)) break;
            if (SDL_KEYUP==event.type) {
                if ('a'==event.key.keysym.sym || 'd'==event.key.keysym.sym) player.turn = 0;
                if ('w'==event.key.keysym.sym || 's'==event.key.keysym.sym) player.walk = 0;
            }
            if (SDL_KEYDOWN==event.type) {
                if ('a'==event.key.keysym.sym) player.turn = -1;
                if ('d'==event.key.keysym.sym) player.turn =  1;
                if ('w'==event.key.keysym.sym) player.walk =  1;
                if ('s'==event.key.keysym.sym) player.walk = -1;
            }
        }

        player.a += float(player.turn)*.05;
        float nx = player.x + player.walk*cos(player.a)*.1;
        float ny = player.y + player.walk*sin(player.a)*.1;


        if (int(nx)>=0 && int(nx)<int(map.w) && int(ny)>=0 && int(ny)<int(map.h) && map.is_empty(nx, ny)) {
            player.x = nx;
            player.y = ny;
        }

        render(gw, map, player, sprites, tex_walls, tex_monst);
        for(auto s : sprites){
            if (s.sprite.player_dist < 0.5){
                player.x = 4.27;
                player.y = 2.345;
                player.a = 1.523;
                player.fov = M_PI/3.;
                player.turn = 0;
                player.walk = 0;
                render(gw, map, player, sprites, tex_walls, tex_monst);
            }
        }
        SDL_UpdateTexture(framebuffer_texture, NULL, reinterpret_cast<void *>(gw.img.data()), gw.w*4);

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, framebuffer_texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(framebuffer_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}