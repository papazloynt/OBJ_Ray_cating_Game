//
// Created by chastikov on 15.04.2021.
//
#ifndef RAY_CAST_MAINPLAYER_H
#define RAY_CAST_MAINPLAYER_H

#include "Object2D.h"
#include "KeyBoard.h"
#include "Draw.h"

class MainPlayer : protected Object2D{
public:
    MainPlayer();
    void movement() override;
    void radius();
private:
    std::vector<RayCastStructure> near_objects;
};
#endif //RAY_CAST_MAINPLAYER_H
