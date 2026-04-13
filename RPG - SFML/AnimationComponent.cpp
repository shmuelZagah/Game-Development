#include "stdafx.h"
#include "AnimationComponent.h"


//--------------------------------
// Animation class implementation
//--------------------------------


AnimationComponent::Animation::Animation(sf::Sprite& sprite, sf::Texture& texturSheets,
	int startFrame_x, int startFrame_y, int frames_x, int frames_y, int width, int hight, float speed, int priority)
	: sprite(sprite), texturSheets(texturSheets), width(width), hight(hight), animationTime(speed), priority(priority)
{
	this->timer = 0.f;
	this->begin = sf::IntRect(startFrame_x * width, startFrame_y * hight, width, hight);
	this->end = sf::IntRect(frames_x * width, frames_y * hight, width, hight);

	this->current = begin;
	this->sprite.setTexture(this->texturSheets, true);
	this->sprite.setTextureRect(this->current);

	done = true;
}

void AnimationComponent::Animation::play(const float& dt, float modPrecent)
{
	//Update timer
	modPrecent = (std::abs(modPrecent) < 0.5f) ? 0.5f : std::abs(modPrecent);

	this->timer += modPrecent * 100.f * dt;

	if (this->timer >= animationTime)
	{
		this->timer = 0.f; //restart time

		if (current != end)
			this->current.left += this->width;
		else {
			this->current = this->begin;
		}
	}
	this->sprite.setTextureRect(this->current);
}

void AnimationComponent::Animation::restart()
{
	this->timer = 0;
	this->current = this->begin;
}





//------------------------------------------
// AnimationComponent class implementation
//------------------------------------------

//C_TOR | D_TOR\\

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture)
	:sprite(sprite), textureSheet(texture), currentAnimation(nullptr)/*, isPlaying(nullptr)*/
{
}

AnimationComponent::~AnimationComponent()
{
	for (auto& pair : animation)
		delete pair.second;
}

bool AnimationComponent::isDone(const  std::string key)
{
	return this->animation[key]->done;
}


//Mathods\\

void AnimationComponent::addAnimtion(const std::string key, int startFrame_x, int startFrame_y, int frames_x, int frames_y,
	int width, int hight, float speed, int priority)
{
	this->animation[key] = new Animation(this->sprite, this->textureSheet, startFrame_x, startFrame_y, frames_x, frames_y, width, hight, speed, priority);
}


//Cover function
void AnimationComponent::play(const std::string key, const float& dt, const float& modifier, const float& modifierMax)
{
	this->play(key, false, dt, modifier, modifierMax);
}


void AnimationComponent::play(const std::string key, bool forcePlayTillEnd, const float& dt, const float& modifier, const float& modifierMax)
{
	//If there is no animation yet
	if (this->currentAnimation == nullptr) this->currentAnimation = this->animation[key];

	//if the priority of the new animtion is higher
	//or the same priority but the current animation
	//isnt force to play till end
	//so chang, in ant other case play the current animation
	else if ((this->animation[key]->priority > this->currentAnimation->priority)
		|| (this->currentAnimation->priority >= this->animation[key]->priority
			&& this->currentAnimation->done
			&& this->currentAnimation != this->animation[key]))
	{
		this->currentAnimation->restart();
		this->currentAnimation->done = true;
		this->currentAnimation = this->animation[key];
		if (forcePlayTillEnd) this->currentAnimation->done = false;
		else this->currentAnimation->done = true;
	}

	//final play
	if (this->currentAnimation == this->animation[key])
		this->currentAnimation->play(dt, modifier / modifierMax);

	//animation finished to play
	if (this->currentAnimation->current == this->currentAnimation->end)
	{
		this->currentAnimation->done = true;
		this->currentAnimation->restart();
		this->currentAnimation = nullptr;
	}
}

