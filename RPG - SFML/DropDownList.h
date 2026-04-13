#pragma once
#include "Lists.h"
#include "ButtonArrow.h"

namespace gui {
	
	class DropDownList 
		: public Lists
	{
		bool isOpen = false;

	public:

		/// <summary>
		///  DropDownList constructor  (vec pos, vec size, vec string names, numOfElements, defultIndex, font)
		/// </summary>
		DropDownList(sf::Vector2f pos, sf::Vector2f size,std::vector<std::string> elements,
			unsigned short numOfElements, unsigned short defultIndex ,sf::Font & font);
		virtual ~DropDownList();

		// Accessors
		bool isOpened() const;

		//Modifiers		
		void setSize(float height, float width) override;

		//Methods
		bool update(const sf::Vector2f& mousePos) override;
		void render(sf::RenderTarget& target) override;
		void reset() override;
	};

}
