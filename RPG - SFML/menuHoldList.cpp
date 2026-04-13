#include "stdafx.h"
#include "menuHoldList.h"


//constructor and destructor\\

gui::menuHoldList::menuHoldList(const sf::Vector2f& pos, const sf::Vector2f& size, const std::vector<std::string>& elements,
	unsigned short numOfElements, unsigned short defultIndex, sf::Font& font, menuHoldList::side side)
	: Lists(pos, size, elements, numOfElements, defultIndex, font)
{
	//Set the position of the active element
	for (int i = 0; i < numOfElements;i++)
	{
		this->elementsList.push_back(new gui::ButtonText(pos.x, pos.y, size.x, size.y,
			elements[i], &this->font,
			sf::Color(20, 30, 40, 250), sf::Color(20, 20, 30, 150), sf::Color(20, 20, 40, 150),
			sf::Color(255, 255, 255, 255), sf::Color(50, 255, 255, 255), sf::Color(50, 200, 255, 255),
			sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255)
		));
		this->elementsList[i]->setId(i);
		this->elementsList[i]->setSizeChangingMode(false);

		switch (side)
		{
		case menuHoldList::LEFT:
			this->elementsList[i]->setPosition({ pos.x - size.x * i , pos.y });
			break;
		case menuHoldList::RIGHT:
			this->elementsList[i]->setPosition({ pos.x + size.x * i , pos.y });
			break;
		case menuHoldList::TOP:
			this->elementsList[i]->setPosition({ pos.x , pos.y - size.y * i });
			break;
		case menuHoldList::BOTTOM:
			this->elementsList[i]->setPosition({ pos.x , pos.y + size.y * i });
			break;
		default:
			break;
		}
	}

	delete this->activeElement;								// Delete the current active element if it exists
	this->activeElement = this->elementsList[defultIndex];	// Set the active element to the one at the default index
	this->activeElement->setStayPressedMode(true);	
	this->activeElement->setState(ButtonStates::BTN_PRESS);
}

gui::menuHoldList::~menuHoldList()
{
}



//Methods\\

bool gui::menuHoldList::update(const sf::Vector2f& mousePos)
{
	if (!this->activeElement->getGlobalBounds().contains(mousePos))
		return false;

	for (auto& it : this->elementsList)
	{
		it->update(mousePos);
		if (it->isPressed() && &it != &this->activeElement)
		{ 
			this->activeElement->setStayPressedMode(false);
			this->activeElement = it;								// Set the active element to the one that was pressed
			this->activeElement->setStayPressedMode(true);			// Set the active element to stay pressed
			it->update(mousePos);
		}
	}
	return true;
}

void gui::menuHoldList::render(sf::RenderTarget& target)
{
	for (auto& it : elementsList)
		it->render(target);
}
