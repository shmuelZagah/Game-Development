#pragma once
enum class DriveState { IDLE = 0, FORWARD, REVERSE, BRAKES };

class DriveComponent
{
private:
    sf::Sprite& sprite;

    float maxVelocity;
    float acceleration;
    float deceleration;
    float brakes;
    bool isBrake;

    float currentSpeed;      // speed > 0
    float currentDirection;     // IDLE = 0 | FORWARD = 1 | BACKWARDS = -1
    int moveDirection;    // direcetion to move to

    sf::Vector2f velocity;

public:
    DriveComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration, float brakes);
    ~DriveComponent();

    const sf::Vector2f getVelocity() const { return this->velocity; }

    void update(const float& dt);
    void move(int side);
    void move(DriveState state);
    void stop();
    bool getState(DriveState state);
};


