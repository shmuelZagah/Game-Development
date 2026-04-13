#include "stdafx.h"
#include "RotationComponent.h"

//----------------------------------------
// RotationComponent class implementation
//----------------------------------------

RotationComponent::RotationComponent(sf::Sprite& sprite, float maxspeed, float acceleration, float deceleration)
	: sprite(sprite), maxVelocity(maxspeed), acceleration(acceleration), deceleration(deceleration)
{
	this->velocity = 0;
}

RotationComponent::~RotationComponent()
{
}

void RotationComponent::update(const float& dt)
{
	// Apply deceleration
	if (velocity > 0)
	{
		velocity -= deceleration;
		if (velocity < 0)
			velocity = 0;
	}
	else if (velocity < 0)
	{
		velocity += deceleration;
		if (velocity > 0)
			velocity = 0;
	}

	// Apply rotation
	sprite.rotate(velocity * dt);
}

void RotationComponent::rotate(float dir)
{
	if (std::abs(velocity) < maxVelocity)
		velocity += dir * acceleration;
	else velocity = maxVelocity * dir;
}

bool RotationComponent::rotateTo(float rotateDir, const float& dt)
{
	float cur = this->sprite.getRotation();
	float delta = rotateDir - cur;

	while (delta > 180.f) delta -= 360.f;
	while (delta < -180.f) delta += 360.f;


	float step = velocity * dt;

	//if close to Dir
	if (std::abs(delta) < std::abs(step)) {
		this->velocity = 0;
		this->sprite.setRotation(rotateDir);
		return true;
	}

	//rotate
	rotate((delta > 0) ? 1 : -1);
	return false;
}

RotationState RotationComponent::getRotationSide() const
{
	if (velocity > 0) return RotationState::LEFT;
	if (velocity < 0) return RotationState::RIGHT;
	else return RotationState::IDLE;
}

float RotationComponent::getRotationVelocity() const
{
	return this->velocity;
}

void RotationComponent::setMaxSpeed(float maxSpeed)
{
	this->maxVelocity = maxSpeed;
}

void RotationComponent::track(RotationComponent& other, const float& dt)
{
	this->sprite.rotate(other.getRotationVelocity() * dt);
}




