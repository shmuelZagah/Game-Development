#pragma once

enum  class MovementState { IDLE = 0, MOVE, RIGHT, LEFT, UP, DOWN, KNOCKBACK };


class MovementComponent
{
private:
	//Variables
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	//Effects
	bool knockback;

	sf::Vector2f velocity;

	//initialization functions

public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float accelreation, float deceleration);
	~MovementComponent();

	//Accessors
	const sf::Vector2f getVelocity() const { return this->velocity; }
	const float getMaxVelocity() const { return this->maxVelocity; }

	//Methods
	void update(const float& dt);
	void move(const float dir_x, const float dir_y, const float dt);
	void move(MovementState state, const float& dt);
	bool  getState(MovementState  state);

	void stopKnockback() { this->knockback = false; }
	void knockbackFrom(const sf::FloatRect& attackerPos, float force);
};

