#include "stdafx.h"
#include "Keyboard.h"

std::array<bool, sf::Keyboard::KeyCount> Keybord::keyPrevious{};
std::array<bool, sf::Keyboard::KeyCount> Keybord::keyCurrent{};