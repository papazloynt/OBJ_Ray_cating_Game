// private headers
#include "map.h"

// c++ headers
#include <cassert>

Map::Map() : w(16), h(16) {
    _map = ("1111111111111111"\
          "1              1"\
          "1 111112211111 1"\
          "1 1          1 1"\
          "1 1   1111   1 1"\
          "1 1   1  1   1 1"\
          "1 1   1  1   1 1"\
          "1 1 11    11 1 1"\
          "1 1          1 1"\
          "1 1 11    11 1 1"\
          "1 1   1  1   1 1"\
          "1 1   1  1   1 1"\
          "1 1          1 1"\
          "1 1113    3111 1"\
          "1              1"\
          "1111111111111111");
    assert(_map.size() == w*h);
}

int Map::get(const size_t i, const size_t j) {
    assert(i<w && j<h && _map.size() == w*h);
    return _map[i+j*w] - '0';
}

bool Map::is_empty(const size_t i, const size_t j) {
    assert(i<w && j<h && _map.size() == w*h);
    return _map[i+j*w] == ' ';
}
