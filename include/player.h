#ifndef PLAYER_H
#define PLAYER_H

struct Player {
    float x; // координаты
    float y;
    float a;    // Угол относительно оси Ox
    float fov;  // Обзор
    int turn;
    int walk;
};

#endif // PLAYER_H
