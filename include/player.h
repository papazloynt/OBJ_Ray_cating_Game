#ifndef PLAYER_H
#define PLAYER_H

struct Player {
    float x; // координаты
    float y;
    float a;    // Угол относительно оси Ox
    float fov;  // Обзор
    int turn;
    int walk;
    void init();
};

#endif // PLAYER_H
