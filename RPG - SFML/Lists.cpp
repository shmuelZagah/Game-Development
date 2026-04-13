#include "stdafx.h"
#include "Lists.h"


Lists::Lists(const sf::Vector2f& pos, const sf::Vector2f& size, const std::vector<std::string>& elements,
	unsigned short numOfElements, unsigned short defultIndex, sf::Font& font)
	: font(font)
{
	//defult buttons
	this->activeElement = new gui::ButtonText(pos.x, pos.y, size.x, size.y,
		elements[defultIndex], &this->font,
		sf::Color(20, 30, 40, 250), sf::Color(20, 20, 30, 150), sf::Color(20, 20, 40, 150),
		sf::Color(255, 255, 255, 255), sf::Color(50, 255, 255, 255), sf::Color(50, 200, 255, 255),
		sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255)
	);
	this->activeElement->setOutlineThickness(2.3);
}

//Lists::Lists(const sf::Vector2f& pos, const sf::Vector2f& size, sf::Texture& textur, unsigned short numOfElements, unsigned short defultIndex)
//{
//	//defult buttons
//	this->activeElement = new gui::Button(pos.x, pos.y, size.x, size.y,
//		elements[defultIndex], &this->font,
//		sf::Color(20, 30, 40, 250), sf::Color(20, 20, 30, 150), sf::Color(20, 20, 40, 150),
//		sf::Color(255, 255, 255, 255), sf::Color(50, 255, 255, 255), sf::Color(50, 200, 255, 255),
//		sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255)
//	);
//	this->activeElement->setOutlineThickness(2.3);
//}

Lists::~Lists()
{
	this->activeElement = nullptr;
	delete this->activeElement;

	//delete all the elements in the list
	for (auto& it : this->elementsList)
		if (it) delete it;
}



//Accessors
sf::Vector2f Lists::getPosition() const
{
	return this->activeElement->getPosition();
}

const unsigned short& Lists::getActiveId() const
{
	return this->activeElement->getId();
}

//return true if point is inside active element or any list element
bool Lists::containsPoint(const sf::Vector2f& point) const
{
	if (this->activeElement && this->activeElement->getGlobalBounds().contains(point))
		return true;

	for (auto& it : this->elementsList) {
		if (it && it->getGlobalBounds().contains(point))
			return true;
	}
	return false;
}



//Modifiers

void Lists::setActiveColor(const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor,
	const sf::Color& textIdleColor, const sf::Color& textHoverColor, const sf::Color& textActiveColor, 
	const sf::Color& OLI, const sf::Color& OLH, const sf::Color& OLA)
{
	this->activeElement->setColor(idleColor, hoverColor, activeColor, textIdleColor, textHoverColor, textActiveColor, OLI, OLH, OLA);
}

void Lists::setListColor(const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor,
	const sf::Color& textIdleColor, const sf::Color& textHoverColor, const sf::Color& textActiveColor,
	const sf::Color& OLI, const sf::Color& OLH, const sf::Color& OLA)
{
	{
		for (auto& it : this->elementsList)
		{
			it->setColor(idleColor, hoverColor, activeColor, textIdleColor, textHoverColor, textActiveColor);
		}

		////set the active element color
		//sf::Color temp(idleColor.r - 10 < 0 ? 0 : idleColor.r - 10
		//	, idleColor.g - 10 < 0 ? 0 : idleColor.g - 10
		//	, idleColor.b - 10 < 0 ? 0 : idleColor.b - 10
		//	, idleColor.a + 10 > 255 ? 255 : idleColor.a + 10);

		//if (idleColor.a == 0) temp.a = 0;
		this->activeElement->setColor(idleColor, hoverColor, activeColor, textIdleColor, textHoverColor, textActiveColor, OLI, OLH, OLA);
	}
}

void Lists::setOutLineThickness(float thickness)
{
	this->activeElement->setOutlineThickness(thickness);
}

void Lists::setSize(float height, float width)
{
	this->activeElement->setSize(height, width);
}








//Methods

bool Lists::update(const sf::Vector2f& mousePos)
{
	if (this->activeElement->update(mousePos))
		return true;

	return false;
}

void Lists::render(sf::RenderTarget& target)
{
	this->activeElement->render(target);
}

void Lists::reset()
{
	this->activeElement->reset();
}

bool Lists::isMouseOver(const sf::Vector2f& mousePos)
{
	auto it = elementsList.begin();
	return (std::any_of(it, elementsList.end(),
		[&mousePos](gui::ButtonText* element)
		{ return element->getGlobalBounds().contains(mousePos); }));
}









