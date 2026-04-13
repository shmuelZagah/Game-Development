#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <array>

 class Keybord {
private:
    static std::array<bool, sf::Keyboard::KeyCount> keyPrevious;
    static std::array<bool, sf::Keyboard::KeyCount> keyCurrent;

public:
    static void update() {
        for (int k = 0; k < sf::Keyboard::KeyCount; ++k) {
            keyPrevious[k] = keyCurrent[k];
            keyCurrent[k] = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k));
        }
    }

    static bool justPressed(sf::Keyboard::Key key) {
        return keyCurrent[key] && !keyPrevious[key];
    }

    static bool justReleased(sf::Keyboard::Key key) {
        return keyPrevious[key] && !keyCurrent[key];
    }
};

