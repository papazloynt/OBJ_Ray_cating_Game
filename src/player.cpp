// private headers
#include "player.h"

void Player::init() {
    x = 13;
    y = 1.7;
    a = 3.2;
    fov = M_PI/3.;
    turn = 0;
    walk = 0;
}