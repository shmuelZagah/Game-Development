#pragma once
#include "Button.h"
#include "ButtonArrow.h"

namespace gui {

	class CarouselListTexture
	{
	private:
		std::vector<gui::Button*> buttons;
		sf::Texture& sheet;
		gui::ButtonArrow* next;
		gui::ButtonArrow* previous;
		sf::IntRect texturRect;
		sf::IntRect activeTexturRect;
		sf::RectangleShape renderWindow;
		unsigned maxId;
		unsigned showPictur;
		unsigned short currentId;

	public:
		//Constructor
		CarouselListTexture(const sf::Vector2f& pos, const sf::Texture& textur, unsigned showPictur,
			unsigned numOfPicturs, unsigned sizeOfPictur);
		virtual ~CarouselListTexture();

		//Accessors
		sf::IntRect	getActiveTextureRect() const;

		//Methods
		bool update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);
	};

}