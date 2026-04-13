#include "stdafx.h"
#include "DropDownList.h"


//constructor | destructor\\

gui::DropDownList::DropDownList(sf::Vector2f pos, sf::Vector2f size, std::vector<std::string> elements,
	unsigned short numOfElements, unsigned short defultIndex, sf::Font& font)
	: Lists(pos, size, elements, numOfElements, defultIndex, font)
{
	for (int i = 0; i < numOfElements; i++)
	{
		this->elementsList.push_back(
			new gui::ButtonText(pos.x, pos.y + size.y * (i + 1), size.x, size.y,
				elements[i], &this->font,
				sf::Color(20, 40, 50, 200), sf::Color(20, 20, 30, 50), sf::Color(20, 20, 40, 100),
				sf::Color(255, 255, 255, 255), sf::Color(50, 255, 255, 255), sf::Color(50, 200, 255, 255))
		);
		this->elementsList[i]->setSizeChangingMode(false); //disable size changing effect for the elements
		this->elementsList[i]->setId(i);
	}
	this->activeElement->setSizeChangingMode(false);
}

gui::DropDownList::~DropDownList()
{

}

//Accessors\\

bool gui::DropDownList::isOpened() const
{
	return isOpen;
}

//Modifiers\\

void gui::DropDownList::setSize(float height, float width)
{
	Lists::setSize(height, width);

	int i = 0;
	for (auto& it : elementsList)
	{
		it->setSize(height, width);
		it->setPosition({ this->activeElement->getPosition().x,
			this->activeElement->getPosition().y + this->activeElement->getSize().y * (++i) });
	}
}




//Methods\\

bool gui::DropDownList::update(const sf::Vector2f& mousePos)
{

	if (!this->activeElement->getGlobalBounds().contains(mousePos)
		&& !(this->isOpen && this->isMouseOver(mousePos))) return false;

	Lists::update(mousePos);

	//if active element is pressed
	if (this->activeElement->isPressed())
	{
		this->isOpen = !this->isOpen;
	}

	//if list is open
	if (this->isOpen)
	{
		for (auto& it : this->elementsList)
		{
			if (!it->update(mousePos))
				it->reset();

			//if element is pressed
			if (it->isPressed())
			{
				this->isOpen = false;
				this->activeElement->setText(it->getText());
				this->activeElement->setId(it->getId());
			}
		}
	}
	return true;
}

void gui::DropDownList::render(sf::RenderTarget& target)
{

	if (this->isOpen)
	{
		for (auto& it : this->elementsList)
		{
			it->render(target);
		}
	}

	Lists::render(target);
}

void gui::DropDownList::reset()
{
	Lists::reset();
	if (Mouse::isMouseJustReleased(Mouse::Left)) this->isOpen = false;
}


