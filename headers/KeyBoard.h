//
// Created by chastikov on 15.04.2021.
//

#ifndef RAY_CAST_KEYBOARD_H
#define RAY_CAST_KEYBOARD_H

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <array>

class KeyBoard{
public:
    Keyboard();
    void update(sf::Event e);
    bool isKeyDown(sf::Keyboard::Key key) const;
private:
    void resetKeys();
    std::array<bool, sf::Keyboard::KeyCount> m_keys;
};
#endif //RAY_CAST_KEYBOARD_H
