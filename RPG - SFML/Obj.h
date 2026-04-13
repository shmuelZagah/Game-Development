#pragma once
#include "SFML/Graphics.hpp"

class Obj
{
public:
	virtual ~Obj() = default;
	
	virtual bool update(const sf::Vector2f& mousePos) = 0;
	virtual void render(sf::RenderTarget& target) =0;
	virtual bool isMouseOver(const sf::Vector2f& mousePos) = 0;
	virtual void reset() = 0;
};

