#include "stdafx.h"
#include "MovementComponent.h"

//Constructor | Destructor
MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float accelreation, float deceleration)
	:sprite(sprite)
{
	this->maxVelocity = maxVelocity;
	this->acceleration = accelreation;
	this->deceleration = deceleration;
	this->knockback = false;
}

MovementComponent::~MovementComponent()
{

}

//Functions
void MovementComponent::update(const float& dt)
{
	//Deceleration

	//Dir_x
	if (this->velocity.x > 0)
	{
		this->velocity.x -= this->deceleration;
		if (this->velocity.x < 0)this->velocity.x = 0;
	}
	if (this->velocity.x < 0)
	{
		this->velocity.x += this->deceleration;
		if (this->velocity.x > 0)this->velocity.x = 0;
	}

	//Dir_Y
	if (this->velocity.y > 0)
	{
		this->velocity.y -= this->deceleration;
		if (this->velocity.y < 0)this->velocity.y = 0;
	}
	if (this->velocity.y < 0)
	{
		this->velocity.y += this->deceleration;
		if (this->velocity.y > 0)this->velocity.y = 0;
	}

	//Final move
	this->sprite.move(velocity * dt);
}

void MovementComponent::move(const float dir_x, const float dir_y, const float dt)
{
	//Acceleration
	this->velocity.x += dir_x * this->acceleration;
	if (this->velocity.x > maxVelocity) this->velocity.x = this->maxVelocity;
	else if (this->velocity.x < -maxVelocity) this->velocity.x = -this->maxVelocity;

	this->velocity.y += dir_y * this->acceleration;
	if (this->velocity.y > maxVelocity) this->velocity.y = this->maxVelocity;
	else if (this->velocity.y < -maxVelocity) this->velocity.y = -this->maxVelocity;

}

void MovementComponent::move(MovementState state, const float& dt)
{
	switch (state)
	{
	case MovementState::IDLE: velocity = { 0,0 };								break;
	case MovementState::MOVE:													break;
	case MovementState::RIGHT: move(1, 0, dt);									break;
	case MovementState::LEFT:move(-1, 0, dt);									break;
	case MovementState::UP:move(0, 1, dt);										break;
	case MovementState::DOWN:move(0, -1, dt);									break;
	case MovementState::KNOCKBACK:
		this->velocity.x = (sprite.getScale().x > 0 ? -maxVelocity : maxVelocity);
		this->velocity.y = 0;
		knockback = true;
	}
}

bool MovementComponent::getState(MovementState state)
{
	switch (state)
	{
	case MovementState::KNOCKBACK: return this->knockback;						break;
	case MovementState::IDLE:return velocity.x == 0 && velocity.y == 0;		break;
	case MovementState::MOVE: return velocity.x != 0 || velocity.y != 0;	break;
	case MovementState::RIGHT: return velocity.x > 0;						break;
	case MovementState::LEFT: return velocity.x < 0;						break;
	case MovementState::UP:return  velocity.y < 0;							break;
	case MovementState::DOWN: return velocity.y > 0;						break;
	default: return false;													break;
	}

	return false;
}

void MovementComponent::knockbackFrom(const sf::FloatRect& attackerPos, float force)
{
	this->velocity.x = (sprite.getPosition().x < attackerPos.getPosition().x) ? -force : force;

	this->knockback = true;
}

