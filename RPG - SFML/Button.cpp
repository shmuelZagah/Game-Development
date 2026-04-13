#include "stdafx.h"
#include "Button.h"
#include "ButtonText.h"


//constructor | destructor\\


gui::Button::Button(float x, float y, float width, float height,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
	sf::Color outLineIdleColor, sf::Color OutLineHoverColor, sf::Color OutLineActiveColor)

	:backgroundColor(new EditorColorBK(idleColor, hoverColor, activeColor)),
	outLineColor(new EditorColorOL(outLineIdleColor, OutLineHoverColor, OutLineActiveColor)),
	buttonState((short)ButtonStates::BTN_IDLE), sizeChangingMode(true), id(0),
	width(width), height(height), stayPressed(false), textur(nullptr)
{
	shape = new sf::RectangleShape;
	this->setSize(width, height);
	this->shape->setPosition(x, y);

	this->shape->setFillColor(this->backgroundColor->getIdle()); //restart color as idle
	if (outLineIdleColor == sf::Color::Transparent) this->setOutlineThickness(0);
}


//copy constructor
gui::Button::Button(const Button& other)
{
	// copy background color
	this->backgroundColor = new EditorColorBK(
		other.backgroundColor->getIdle(),
		other.backgroundColor->getHover(),
		other.backgroundColor->getActive()
	);

	this->outLineColor = new EditorColorOL(
		other.outLineColor->getIdle(),
		other.outLineColor->getHover(),
		other.outLineColor->getActive()
	);

	this->sizeChangingMode = other.sizeChangingMode;
	this->buttonState = (short)ButtonStates::BTN_IDLE;
	this->setSize(other.getGlobalBounds().width, other.getGlobalBounds().height);
	this->shape->setPosition(other.getPosition());

	this->setColor(other.backgroundColor->getIdle(), other.backgroundColor->getHover(), other.backgroundColor->getActive(),
		other.outLineColor->getIdle(), other.outLineColor->getHover(), other.outLineColor->getActive());

	this->shape->setFillColor(this->backgroundColor->getIdle());

	this->stayPressed = other.stayPressed;
}


gui::Button::~Button()
{
	delete this->backgroundColor;
	delete this->outLineColor;
}



//Accessors
const bool gui::Button::isPressed() const
{
		return this->buttonState == (short)ButtonStates::BTN_ACTIVE;
}

const unsigned short gui::Button::pressingState() const
{
	return this->buttonState;
}


short unsigned gui::Button::getId() const
{
	return this->id;
}

sf::Vector2f gui::Button::getSize() const
{
	return { this->width,this->height };
}

bool gui::Button::isSizeChanging() const
{
	return sizeChangingMode;
}

bool gui::Button::isStayPressed() const
{
	return stayPressed; 
}


//Modifiers

void gui::Button::setPosition(const sf::Vector2f& pos)
{
	this->shape->setPosition(pos);
}

void gui::Button::setSizeChangingMode(bool toDo)
{
	this->sizeChangingMode = toDo;
}

void gui::Button::setId(short unsigned id)
{
	this->id = id;
}

void gui::Button::setSize(float width, float height)
{
	this->setShapeSize({ width,height });
	this->shape->setOrigin(width / 2, height / 2);
}

void gui::Button::rotate(float deg) {
	this->shape->rotate(deg);
}

void gui::Button::setTextur(sf::Texture& textur)
{
	this->textur = &textur;
	this->shape->setTexture(this->textur);
}

void gui::Button::setTexturRect(const sf::IntRect& rect)
{
	this->shape->setTextureRect(rect);
}

void gui::Button::setState(ButtonStates state)
{
	this->buttonState = (short)state;
	// Update the button color based on its state
	this->updateColors();
}

void gui::Button::setStayPressedMode(bool state)
{
	this->stayPressed = state;
}


//Function

bool gui::Button::update(const sf::Vector2f& mousePos)
{
	//  Early out - mouse not over button
	if (!this->shape->getGlobalBounds().contains(mousePos))
	{
		return false;
	}
		

	/*Button Pressed*/

	// Update the button state based on mouse position
	if (stayPressed) this->buttonState = (short)ButtonStates::BTN_PRESS;
	else {

		//default
		this->buttonState = (short)ButtonStates::BTN_IDLE;


		// Check if the mouse is over the button
		if (this->shape->getGlobalBounds().contains(mousePos))
		{
			this->buttonState = (short)ButtonStates::BTN_HOVER;

			// check if the button is pressed
			if (Mouse::isMouseJustReleased(Mouse::Left))
			{
				this->buttonState = (short)ButtonStates::BTN_ACTIVE;
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->buttonState = (short)ButtonStates::BTN_PRESS;
			}
		}
	}
	// Update the button color based on its state
	this->updateColors();

	return true;
}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(*this->shape);
}

bool gui::Button::isMouseOver(const sf::Vector2f& mousePos)
{
	return this->shape->getGlobalBounds().contains(mousePos);
}

void gui::Button::reset()
{
	this->buttonState = (short)ButtonStates::BTN_IDLE;
	this->updateColors();
}




//_______________private functions________________________\\

void gui::Button::updateColors()
{

	switch (this->buttonState)
	{
	case (short)ButtonStates::BTN_IDLE:
		this->shape->setFillColor(this->backgroundColor->getIdle());
		this->shape->setOutlineColor(this->outLineColor->getIdle());
		this->shape->setScale(1, 1);
		break;
	case (short)ButtonStates::BTN_HOVER:
		this->shape->setFillColor(this->backgroundColor->getHover());
		this->shape->setOutlineColor(this->outLineColor->getHover());
		if (this->sizeChangingMode && this->shape->getScale().x < 1.05f)
		{
			this->shape->setScale(this->shape->getScale().x+0.002, this->shape->getScale().y + 0.002);
		}
		break;
	case (short)ButtonStates::BTN_PRESS:
		this->shape->setFillColor(this->backgroundColor->getActive());
		this->shape->setOutlineColor(this->outLineColor->getActive());
		break;

	default:
		this->shape->setFillColor(this->backgroundColor->getIdle());
		this->shape->setOutlineColor(this->outLineColor->getIdle());
		this->shape->setScale(1, 1);
		break;
	}
}



sf::Color gui::Button::lighten(const sf::Color& color, int num)
{
	sf::Color temp(color.r + num > 255 ? 255 : color.r + num
		, color.g + num > 255 ? 255 : color.g + num
		, color.b + num > 255 ? 255 : color.b + num
		, color.a + num > 255 ? 255 : color.a + num);

	return temp;
}

sf::Color gui::Button::darken(const sf::Color& color, int num)
{
	sf::Color temp(color.r - 30 < 0 ? 0 : color.r - 30
		, color.g - 30 < 0 ? 0 : color.g - 30
		, color.b - 30 < 0 ? 0 : color.b - 30
		, color.a - 30 < 0 ? 0 : color.a - 30);

	return temp;
}

void gui::Button::setShapeSize(sf::Vector2f vec)
{
	dynamic_cast<sf::RectangleShape*>(this->shape)->setSize(vec);
	this->width = vec.x;
	this->height = vec.y;
}

