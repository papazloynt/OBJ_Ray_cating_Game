//
// Created by chastikov on 15.04.2021.
//

#ifndef RAY_CAST_SCRIPTOBJECT_H
#define RAY_CAST_SCRIPTOBJECT_H

#include "Object2D.h"

class ScriptObject{
public:
    void movement() override;
    void action();
private:
    double radius_action;
};

#endif //RAY_CAST_SCRIPTOBJECT_H
