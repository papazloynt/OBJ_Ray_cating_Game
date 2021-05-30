// private headers
#include "map.h"
#include "ppm_utils.h"
#include "player.h"
#include "sprite.h"
#include "gamewindow.h"
#include "textures.h"
#include "config.h"
#include "spite_drawing.h"

// c++ headers
#include <algorithm>
#include <cmath>
#include <vector>
#include <cassert>

// SDL
#include "SDL.h"

int wall_width_texture_coord(const float x, const float y, WallTexture &tex_walls) {
    float hitx = x - floor(x+.5);
    float hity = y - floor(y+.5);
    int tex = hitx * tex_walls.size;
    if (std::abs(hity) > std::abs(hitx))
        tex = hity * tex_walls.size;
    if (tex < 0) // Если отрицательное, то обрабатываем этот случай
        tex += tex_walls.size;
    assert(tex >= 0 && tex< (int)tex_walls.size);
    return tex;
}


void render(GameWindow &gw, Map &map, Player &player, std::vector<SpriteDrawing> &sprites, WallTexture &tex_walls, WallTexture &tex_pers) {
    gw.clear(ppm::pack_color(255, 255, 255));
    const size_t rect_w = gw.w / (map.w * 2);
    const size_t rect_h = gw.h / map.h;
    for (size_t j = 0; j < map.h; ++j) {  // Рисуем карту
        for (size_t i = 0; i < map.w; ++i) {
            if (map.is_empty(i, j)) continue; // Пропускаем, если пробел
            size_t rect_x = i*rect_w;
            size_t rect_y = j*rect_h;
            size_t texid = map.get(i, j);
            assert(texid<tex_walls.count);
            gw.draw_rectangle(rect_x, rect_y, rect_w, rect_h, tex_walls.get(0, 0, texid)); // Верхний пиксель текстуры
        }
    }

    std::vector<float> depth_buffer(gw.w/2, 1e3);
    for (size_t i = 0; i < gw.w / 2; ++i) { // рисуем видимую область
        float angle = player.a - player.fov / 2 + player.fov * i / float(gw.w/2);
        for (float t = 0; t < 20; t += .01) { // размер луча
            float x = player.x + t*cos(angle);
            float y = player.y + t*sin(angle);
            gw.set_pixel(x*rect_w, y*rect_h, ppm::pack_color(160, 160, 160)); // Луч видимости на карте

            if (map.is_empty(x, y)) continue;

            size_t texid = map.get(x, y);
            assert(texid < tex_walls.count);
            float dist = .2+t * cos(angle-player.a);
            depth_buffer[i] = dist;
            size_t column_height = gw.h/dist;
            int x_texcoord = wall_width_texture_coord(x, y, tex_walls);
            std::vector<uint32_t> column = tex_walls.get_scaled_column(texid, x_texcoord, column_height);
            int pix_x = i + gw.w/2;

            for (size_t j = 0; j < column_height; j++) {
                int pix_y = j + gw.h/2 - column_height/2;
                if (pix_y >= 0 && pix_y < (int)gw.h) {
                    gw.set_pixel(pix_x, pix_y, column[j]);
                }
            }
            break;
        }
    }
    //Костыль, но он работает.
    for (size_t i = 0; i < sprites.size(); ++i) { // Обновляем расстояние от игрока до каждого спрайта
        sprites[i].sprite.player_dist = std::sqrt(pow(player.x - sprites[i].sprite.x, 2) + pow(player.y - sprites[i].sprite.y, 2));
    }
    std::sort(sprites.begin(), sprites.end()); // Сортируем их от дальних, к ближним

    for (size_t i = 0; i < sprites.size(); ++i) {
        sprites[i].map_show_sprite(gw, map);
        sprites[i].draw_sprite(depth_buffer, gw, player, tex_pers);
    }
}

// сущность алгоритмы

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
            if (s.sprite.player_dist < 0.3){
                return -1;
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