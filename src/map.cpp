// private headers
#include "map.h"

// c++ headers
#include <cassert>

Map::Map() : w(16), h(16) {
    _map = ("0000222222220000"\
          "1              0"\
          "1       1111   0"\
          "1     1        0"\
          "1     1  1110000"\
          "0     1        0"\
          "1   10000      0"\
          "0   3   11100  0"\
          "5   4   0      0"\
          "5   4   1  00000"\
          "0       1      0"\
          "2       1      0"\
          "0       1      0"\
          "0 000000       0"\
          "0              0"\
          "0002222222200000");
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
