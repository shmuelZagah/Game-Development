#include "stdafx.h"
#include "CarouselList.h"

gui::CarouselList::CarouselList(sf::Vector2f pos, sf::Vector2f size, std::vector<std::string> elements,
	unsigned short numOfElements, unsigned short defultIndex, sf::Font& font)
	:Lists(pos, size, elements, numOfElements, defultIndex, font)
{
	this->next = new gui::ButtonArrow(pos.x + size.x / 2 + size.y/2, pos.y, size.y/2, size.y/2);
	this->next->rotate(90);

	this->back = new gui::ButtonArrow(pos.x - size.x / 2 - size.y/2, pos.y, size.y/2, size.y/2);
	this->back->rotate(-90);

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

gui::CarouselList::~CarouselList()
{
	delete this->next;
	delete this->back;
}

void gui::CarouselList::setArrowTextur(sf::Texture& t)
{
	this->next->setTextur(t);
	this->back->setTextur(t);
}


//Methods\\ 

bool gui::CarouselList::update(const sf::Vector2f& mousePos)
{
	if (!(Lists::update(mousePos) || this->next->update(mousePos) || this->back->update(mousePos)))
		return false;

	int id = this->getActiveId();

	//go next
	if (this->next->isPressed())
	{
		if (id >= elementsList.size() - 1)
			id = 0;
		else
			id++;
	}

	//go back
	if (this->back->isPressed())
	{
		if (id <= 0)
			id = this->elementsList.size() - 1;
		else
			id--;
	}

	this->activeElement->setId(this->elementsList[id]->getId());
	this->activeElement->setText(this->elementsList[id]->getText());

	return true;

}

void gui::CarouselList::render(sf::RenderTarget& target)
{
	Lists::render(target);
	this->next->render(target);
	this->back->render(target);
}
