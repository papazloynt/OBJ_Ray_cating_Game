#ifndef MAP_H
#define MAP_H
// c++ headers
#include <string>

struct Map {
    size_t w;
    size_t h;
    std::string _map;
    Map();
    int get(const size_t i, const size_t j);
    bool is_empty(const size_t i, const size_t j);
};

#endif // MAP_H