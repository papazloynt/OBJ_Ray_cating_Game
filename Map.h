#ifndef OBJGAME_MAP_H
#define OBJGAME_MAP_H

#include <iostream>
#include <vector>

struct Map {
    std::vector<int> map;

    Map();

    int getTile(int x, int y) const;
};

#endif //OBJGAME_MAP_H