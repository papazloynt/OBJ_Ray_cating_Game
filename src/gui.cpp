// private headers
#include "render.h"
#include "draw_fon_button.h"

// c++ headers
#include <cmath>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

// SDL
#include "SDL.h"

[[noreturn]] void movement_sprite_around(SpriteDrawing& s){
    std::mutex _mutex;
    while (true) {
        _mutex.lock();
        while (s.sprite.y < s.max_coord) {
               s.sprite.y += s.sprite.speed;
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        s.sprite.y -= s.sprite.speed;
        while(s.sprite.x < s.max_coord){
            s.sprite.x += s.sprite.speed;
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        s.sprite.x -= s.sprite.speed;
        while(s.sprite.y > s.min_coord){
            s.sprite.y -= s.sprite.speed;
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        s.sprite.y += s.sprite.speed;
        while(s.sprite.x > s.min_coord){
            s.sprite.x -= s.sprite.speed;
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        s.sprite.x += s.sprite.speed;
        _mutex.unlock();
    }
}

int main() {
    GameWindow gw{1024, 512, std::vector<uint32_t>(1024*512, ppm::pack_color(255, 255, 255))};
    Player player{13, 1.7, 3.2, M_PI/3., 0, 0};

    Map map;

    WallTexture tex_walls("../img/walltext.bmp", SDL_PIXELFORMAT_ABGR8888);
    WallTexture tex_monst("../img/bicycle_1.bmp", SDL_PIXELFORMAT_ABGR8888);

    if (!tex_walls.count) {
        std::cerr << "Failed to load textures" << std::endl;
        return -1;
    }
    std::vector<SpriteDrawing> sprites{ SpriteDrawing{Sprite{1.4, 9, 0, 0, 0.02},14.4, 1.5},
                                        SpriteDrawing{Sprite{3.5, 9, 0, 0, 0.01},12, 3.5}};

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

    // Меню и инструкция
    {
        DrawFonButton menu("../img/start.bmp", "../img/fon.bmp");
        menu.draw_static(renderer);

        DrawFonButton instr("../img/start.bmp", "../img/instruction.bmp");
        instr.draw_static(renderer);
    }

    std::vector<std::thread> threads;
    for (size_t i = 0; i < sprites.size(); ++i){
        threads.emplace_back(movement_sprite_around, std::ref(sprites[i]));
        threads[i].detach();
    }

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

        player.a += float(player.turn) * 0.05;
        float nx = player.x + player.walk*cos(player.a)*.1;
        float ny = player.y + player.walk*sin(player.a)*.1;


        if (int(nx) >= 0 && int(nx) < int(map.w) && int(ny) >= 0 && int(ny) < int(map.h) && map.is_empty(nx, ny)) {
            player.x = nx;
            player.y = ny;
        }

        // Рендерим то, что есть
        render(gw, map, player, sprites, tex_walls, tex_monst);

        for (auto s : sprites) {
            if (s.sprite.player_dist < 0.35){
                {
                    DrawFonButton restart("../img/try_again.bmp", "../img/instruction.bmp");
                    restart.draw_static(renderer);
                }
                player.init();
                render(gw, map, player, sprites, tex_walls, tex_monst);
            }
        }

        if (player.x >= 7 && player.x <= 9 && player.y >= 3 && player.y <= 3.5){
            {
                DrawFonButton restart("../img/win.bmp", "../img/instruction.bmp");
                restart.draw_static(renderer);
            }
            player.init();
            render(gw, map, player, sprites, tex_walls, tex_monst);
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