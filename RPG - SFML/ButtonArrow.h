#pragma once
#include "Button.h"

namespace gui {
	class ButtonArrow
		:public gui::Button
	{
	public:
		ButtonArrow(float x, float y, float width, float height,
			sf::Color idleColor = sf::Color::White,
			sf::Color hoverColor = sf::Color::White,
			sf::Color activeColor = sf::Color::White,
			sf::Color outLineIdleColor = sf::Color::Transparent,
			sf::Color OutLineHoverColor = sf::Color::Transparent,
			sf::Color OutLineActiveColor = sf::Color::Transparent);

		~ButtonArrow();

		// Override
		virtual void setSize(float width, float height) override;

	private:
		virtual void setShapeSize(sf::Vector2f vec) override;
	};
}

