#include "stdafx.h"
#include "Mouse.h"


//constructor | destructor\\    

Mouse::Mouse(sf::RenderWindow& window) :isPressingLeft(false)
{
	if (!font.loadFromFile("Fonts/BRLNSR.TTF"))
		std::cerr << "Failed to load font!" << std::endl;


	window.setMouseCursorVisible(false);
	positionText.setCharacterSize(14);
	positionText.setFillColor(sf::Color::White);
	sprite.setColor(sf::Color(220, 200, 255, 255));
	loadTexture();

}

bool Mouse::loadTexture() {
	if (!texture.loadFromFile("Resources/Images/Mouse/mouse_idle2.png"))
		return false;

	sprite.setTexture(texture);

	positionText.setFont(font);
	positionText.setString("x:0, y:0");
	return true;
}

void Mouse::setGridSizeU(unsigned gridSizeU)
{
	this->gridSizeU = gridSizeU;
}



//Accessors\\

//bool Mouse::isMouseJustReleased()
//{
//	return isRelesedLeft;
//}

bool Mouse::isMouseJustReleased(Mouse::key k)
{
	switch (k)
	{
	case Left: return isRelesedLeft;
	case Right:return isRelesedRight;
	}
}




//Function\\

void Mouse::update(const sf::RenderWindow& window) {
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);


	this->updatePosXy(worldPos);
	this->updateMouseJustReleased();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sprite.setScale(1, 0.98);
	}
	else
	{
		sprite.setScale(1, 1);
		sprite.setPosition(worldPos.x, worldPos.y - 2);
	}
	sprite.setTexture(texture);
}

void Mouse::updatePosXy(sf::Vector2f& worldPos)
{
	sprite.setPosition(worldPos.x, worldPos.y);


	positionText.setPosition(worldPos.x + 30.f, worldPos.y - 10.f);

	positionText.setString(
		std::to_string((int)worldPos.x) + "/" + std::to_string((int)worldPos.y) + "\n"
		+ std::to_string((int)worldPos.x / this->gridSizeU) + "/" + std::to_string((int)worldPos.y / this->gridSizeU));
}



void Mouse::render(sf::RenderTarget& target) {

	target.draw(sprite);
	target.draw(positionText);
}



//Functions - private
bool Mouse::isRelesedLeft = false;
bool Mouse::isRelesedRight = false;

void Mouse::updateMouseJustReleased()
{

	// Left mouse button
	if (isPressingLeft && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		isPressingLeft = false;
		isRelesedLeft = true;
	}

	else
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			isPressingLeft = true;
		isRelesedLeft = false;
	}

	// Right mouse button
	if (isPressingRight && !sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		isPressingRight = false;
		isRelesedRight = true;
	}

	else
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			isPressingRight = true;
		isRelesedRight = false;
	}
}
	
