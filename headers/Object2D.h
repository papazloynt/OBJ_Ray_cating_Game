//
// Created by chastikov on 15.04.2021.
//
#ifndef RAY_CAST_OBJECT2D_H
#define RAY_CAST_OBJECT2D_H

#include <Point2D.h>

class Object2D{
public:
    Object2D();
    virtual void movement() = 0;
protected:
    Point2D position;
};
#endif //RAY_CAST_OBJECT2D_H
