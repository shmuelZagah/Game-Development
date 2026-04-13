#pragma once
#include "Lists.h"
namespace gui {

	class CarouselList
		: public Lists
	{
	public:
		gui::ButtonArrow* next;
		gui::ButtonArrow* back;

		//constructors
		CarouselList(sf::Vector2f pos, sf::Vector2f size, std::vector<std::string> elements,
			unsigned short numOfElements, unsigned short defultIndex, sf::Font& font);
		virtual ~CarouselList();

		//Modefire
		void setArrowTextur(sf::Texture& t);

		//Methods
		bool update(const sf::Vector2f& mousePos) override;
		void render(sf::RenderTarget& target) override;
		
	};

}