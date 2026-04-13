#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	this->collision = false;
	this->type = TileTypes::DEFAULT;
}

Tile::Tile(float x, float y, float gridSizeF,const sf::Texture& textur, const sf::IntRect& rec, TileTypes type)
{
	this->shape.setSize({ gridSizeF,gridSizeF });
	this->shape.setPosition(x, y);
	this->shape.setFillColor(sf::Color::White);
	this->shape.setTexture(&textur);
	this->shape.setTextureRect(rec);
	this->collision = false;
	this->type = type;
}

Tile::~Tile()
{
}

//Function
void Tile::update() {

}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}


//Methods

// Tile::toString
const std::string Tile::toString()
{
	std::stringstream ss;

	ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " "
		<< this->collision << " " << (int)this->type;

	return ss.str();
}

void Tile::setCollision(const bool collision)
{
	this->collision = collision;
}

