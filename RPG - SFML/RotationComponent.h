#pragma once

//-------------------------------
// RotationComponent class
//--------------------------------

enum class RotationState { IDLE = 0, LEFT, RIGHT };

class RotationComponent
{
private:
	//Variables
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	float velocity;

public:
	RotationComponent(sf::Sprite& sprite, float maxspeed, float acceleration, float deceleration);
	~RotationComponent();


	//main Fanction
	void update(const float& dt);



	//Getters  - Setters
	RotationState getRotationSide() const;
	float getRotationVelocity() const;

	void setMaxSpeed(float maxSpeed);


	//Methods
	void rotate(float rotateSide);
	bool rotateTo(float rotateDir, const float& dt); //Rotate in the shortest way to the wanted direction
	void track(RotationComponent& other, const float& dt); //Following another sprite | Matching its rotation

	};


