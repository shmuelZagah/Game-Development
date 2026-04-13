#pragma once
#include "Lists.h"

namespace gui
{
	class menuHoldList
		:public Lists
	{
	public:

		enum side {
			LEFT,
			RIGHT,
			TOP,
			BOTTOM
		};

		menuHoldList(const sf::Vector2f& pos, const sf::Vector2f& size, const std::vector<std::string>& elements,
			unsigned short numOfElements, unsigned short defultIndex, sf::Font& font, menuHoldList::side side);


		virtual ~menuHoldList();

		//Methods
		bool update(const sf::Vector2f& mousePos) override;
		void render(sf::RenderTarget& target) override;
	};

}