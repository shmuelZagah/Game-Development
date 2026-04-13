#include "stdafx.h"
#include "Button.h"
#include "ButtonText.h"

//------------------------------------------
// Color Function - implementation
//------------------------------------------

gui::Button::EditorColorBK& gui::Button::BackgroundColor()
{
	return *this->backgroundColor;
}

gui::ButtonText::EditorColorTX& gui::ButtonText::TextColor()
{
	return *this->textColor;
}



void gui::Button::setColor(const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor,
	const sf::Color& outLineIdleColor, const sf::Color& OutLineHoverColor, const sf::Color& OutLineActiveColor)
{
	this->backgroundColor->setIdle(idleColor);
	this->backgroundColor->setHover(hoverColor);
	this->backgroundColor->setActive(activeColor);
	this->outLineColor->setIdle(outLineIdleColor);
	this->outLineColor->setHover(OutLineHoverColor);
	this->outLineColor->setActive(OutLineActiveColor);
	//update the colors
	this->updateColors();
}



void gui::Button::setBackgroundColor(const sf::Color& idleColor, int x)
{
	this->backgroundColor->setIdle(idleColor);
	this->backgroundColor->setHover(this->lighten(idleColor, x));
	this->backgroundColor->setActive(this->darken(idleColor, x));
	this->updateColors();
}



void gui::Button::setOutLine(const sf::Color& outLineColor)
{
	this->outLineColor->setColor(outLineColor);
	this->updateColors();
}

void gui::Button::setOutlineThickness(float x)
{
	this->shape->setOutlineThickness(x);
}
