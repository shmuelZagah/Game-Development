#include "stdafx.h"
#include "DriveComponent.h"

DriveComponent::DriveComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration, float brakes)
	:sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration),
	currentSpeed(0.f), currentDirection(1.f), moveDirection(0), velocity(0.f, 0.f), isBrake(false), brakes(brakes)
{}

DriveComponent::~DriveComponent() {};


void DriveComponent::update(const float& dt)
{
	//netural deceleration
	if (currentSpeed > 0.f) // if is moving
	{
		if (isBrake)   currentSpeed -= (deceleration * brakes) * dt;
		else  currentSpeed -= deceleration * dt;
		if (currentSpeed < 0.f)
			currentSpeed = 0.f;
	}

	//Acceleration with deceleration
	// 
		// Push to the opposite side
	if (currentDirection != moveDirection && currentSpeed > 0.f && moveDirection != 0)
	{
		// deceleration  use the  acceleration
		currentSpeed -= acceleration * dt;
		if (currentSpeed < 0.f)
			currentSpeed = 0.f;
	}
	// if 0
	if (currentSpeed == 0.f)
	{
		currentDirection = moveDirection;
	}
	// push 
	if (currentDirection == moveDirection)
	{
		currentSpeed += acceleration * dt;
		if (currentSpeed > maxVelocity)
			currentSpeed = maxVelocity;
	}


	// direction to move
	float angleRad = (sprite.getRotation()) * 3.14159265f / 180.f;
	sf::Vector2f direction(std::cos(angleRad), std::sin(angleRad));

	velocity = direction * currentSpeed * currentDirection;

	// final move
	sprite.move(velocity * dt);

	// restart for -next frame
	moveDirection = 0;
	isBrake = false;
}

void DriveComponent::move(int side)
{
	moveDirection = side;
}

void DriveComponent::move(DriveState state)
{
	switch (state)
	{
	case DriveState::IDLE: velocity = { 0,0 }; break;
	case DriveState::BRAKES: stop(); break;
	case DriveState::FORWARD: move(1); break;
	case DriveState::REVERSE: move(-1); break;
	}
}

void DriveComponent::stop()
{
	this->isBrake = true;
}


//getters
bool DriveComponent::getState(DriveState state)
{
	switch (state)
	{
	case DriveState::IDLE:
		return velocity.x == 0.f && velocity.y == 0.f;

	case DriveState::FORWARD:
		return moveDirection == 1;

	case DriveState::REVERSE:
		return moveDirection == -1;

	case DriveState::BRAKES: return isBrake;
	}
	return false;
}