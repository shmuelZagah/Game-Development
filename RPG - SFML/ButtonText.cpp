#include "stdafx.h"
#include "ButtonText.h"

//initialization
void gui::ButtonText::initText(const std::string& text)
{
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setCharacterSize((this->height * 0.5f));
	sf::FloatRect textBounds = this->text.getLocalBounds();
	this->restartTextOrigin();
	this->text.setPosition(shape->getPosition().x, shape->getPosition().y);
}


//constructors 
gui::ButtonText::ButtonText(float x, float y, float width, float hieght, std::string text, sf::Font* font,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
	sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
	sf::Color outLineIdleColor, sf::Color OutLineHoverColor, sf::Color OutLineActiveColor)

	: Button(x, y, width, hieght, idleColor, hoverColor, activeColor, outLineIdleColor, OutLineHoverColor, OutLineActiveColor),
	textColor(new EditorColorTX(textIdleColor, textHoverColor, textActiveColor))
{
	this->font = font;

	// init Text Properties
	this->initText(text);
}

gui::ButtonText::ButtonText(const ButtonText& other) : Button(other)
{
	this->textColor = new EditorColorTX(
		other.textColor->getIdle(),
		other.textColor->getHover(),
		other.textColor->getActive());

	// init Text Properties
	this->font = other.font;
	this->initText(other.getText());

	this->TextColor().setIdle(other.textColor->getIdle());
	this->TextColor().setHover(other.textColor->getHover());
	this->TextColor().setActive(other.textColor->getActive());

	this->setSize(other.getGlobalBounds().width, other.getGlobalBounds().height);
	this->shape->setPosition(other.getPosition());
}

gui::ButtonText::~ButtonText()
{
	delete this->textColor;
}

//Accessors
std::string gui::ButtonText::getText() const
{
	return this->text.getString();
}

//Modifiers
void gui::ButtonText::setText(const std::string& text)
{
	this->text.setString(text);
	this->restartTextOrigin();
}

void gui::ButtonText::setPosition(const sf::Vector2f& pos)
{
	Button::setPosition(pos);
	this->text.setPosition(pos.x, pos.y);
}

void gui::ButtonText::setSize(float width, float hieght)
{
	this->text.setCharacterSize((this->getGlobalBounds().height * 0.5f));
	this->restartTextOrigin();
}


//Color - Function
void gui::ButtonText::setColor(const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor,
	const sf::Color& textIdleColor, const sf::Color& textHoverColor, const sf::Color& textActiveColor,
	const sf::Color& outLineIdleColor, const sf::Color& OutLineHoverColor, const sf::Color& OutLineActiveColor)
{
	this->textColor->setIdle(textIdleColor);;
	this->textColor->setHover(textHoverColor);
	this->textColor->setActive(textActiveColor);
	Button::setColor(idleColor, hoverColor, activeColor, outLineIdleColor, OutLineHoverColor, OutLineActiveColor);
	//update the colors
	this->updateColors();
}

gui::Button::EditorColorOL& gui::Button::OutLine()
{
	return *this->outLineColor;
}

void gui::ButtonText::setTextColor(const sf::Color& textIdleColor, int x)
{
	this->textColor->setIdle(textIdleColor);
	this->textColor->setHover(this->lighten(textIdleColor, x));
	this->textColor->setActive(this->darken(textIdleColor, x));
	this->updateColors();
}


//Function
void gui::ButtonText::render(sf::RenderTarget& target)
{
	Button::render(target);
	target.draw(this->text);
}


//Private functions
void gui::ButtonText::updateColors()
{
	Button::updateColors();

	switch (this->buttonState)
	{
	case (short)ButtonStates::BTN_IDLE:
		this->text.setFillColor(this->textColor->getIdle());
		this->text.setScale(1, 1);
		break;
	case (short)ButtonStates::BTN_HOVER:
		this->text.setFillColor(this->textColor->getHover());
		if (this->sizeChangingMode && this->text.getScale().x < 1.05f)
			this->text.setScale(this->text.getScale().x + 0.002, this->text.getScale().y + 0.002);
		break;
	case (short)ButtonStates::BTN_PRESS:
		this->text.setFillColor(this->textColor->getActive());
		if (this->sizeChangingMode)
			this->text.setScale(0.95f, 0.95f);
		break;

	default:
		this->text.setFillColor(this->textColor->getHover());
		this->text.setScale(1, 1);
		break;
	}
}


void gui::ButtonText::restartTextOrigin()
{
	//put the anchor of the text to the center of the buutton
	sf::FloatRect textBounds = this->text.getLocalBounds();
	this->text.setOrigin(
		textBounds.left + textBounds.width / 2.f,
		textBounds.top + textBounds.height / 2.f
	);
}


