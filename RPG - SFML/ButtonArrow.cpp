#include "stdafx.h"
#include "ButtonArrow.h"



//constructors

gui::ButtonArrow::ButtonArrow(float x, float y, float width, float height,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
	sf::Color outLineIdleColor, sf::Color OutLineHoverColor, sf::Color OutLineActiveColor)

	:Button(x, y, width, height, idleColor, hoverColor, activeColor, outLineIdleColor, OutLineHoverColor, OutLineActiveColor)
{
	delete this->shape;
	auto* tri = new sf::ConvexShape(3);
	this->shape = tri;
	this->setSize(width, height);
	this->shape->setPosition(x, y);

	this->shape->setFillColor(this->backgroundColor->getIdle()); //restart color as idle
	if (outLineIdleColor == sf::Color::Transparent) this->setOutlineThickness(0);
}

gui::ButtonArrow::~ButtonArrow()
{
	//noghing to do right now
}

//_______________private functions________________________\\

void gui::ButtonArrow::setSize(float width, float height)
{
	this->setShapeSize({ width, height });
	this->shape->setOrigin(width / 2, height / 2);
	this->rotate(180);
}

void gui::ButtonArrow::setShapeSize(sf::Vector2f vec)
{
	dynamic_cast<sf::ConvexShape*>(this->shape)->setPoint(0, sf::Vector2f(0, 0));
	dynamic_cast<sf::ConvexShape*>(this->shape)->setPoint(1, sf::Vector2f(vec.x, 0));
	dynamic_cast<sf::ConvexShape*>(this->shape)->setPoint(2, sf::Vector2f(vec.x/2, vec.y));
}
