#include "stdafx.h"
#include "HitboxComponent.h"
#include "HealthComponent.h"

//-------------------------------
// HitboxComponent class implementation
//--------------------------------


//constructors | distractors \\

HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float hight)
	:sprite(sprite)
{

	hitBox.setSize({ width, hight });
	this->hitBox.setScale(this->sprite.getScale());
	this->hitBox.setOrigin(
		{
			(this->hitBox.getLocalBounds().left + this->hitBox.getLocalBounds().width) / 2,
			(this->hitBox.getLocalBounds().top + this->hitBox.getLocalBounds().height) / 2,
		});
	this->hitBox.setPosition(this->sprite.getPosition().x - offset_x, this->sprite.getPosition().y - offset_y);


	offset = { offset_x,offset_y };

	//hitbox
	hitBox.setFillColor(sf::Color::Transparent);
	hitBox.setOutlineColor(sf::Color::Red);
	hitBox.setOutlineThickness(1);
}

HitboxComponent::~HitboxComponent()
{

}



//Methods\\

bool HitboxComponent::checkIntersect(const sf::FloatRect& frect)
{
	return this->hitBox.getGlobalBounds().intersects(frect);
}



//Accessors\\

sf::FloatRect HitboxComponent::getBounds() const
{
	return this->hitBox.getGlobalBounds();
}




//-------------------------------------------------
//				Main Methods
//-------------------------------------------------


void HitboxComponent::update()
{
	this->hitBox.setPosition(this->sprite.getPosition().x - offset.x, this->sprite.getPosition().y - offset.y);
	this->hitBox.setRotation(this->sprite.getRotation());
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(this->hitBox);
}




