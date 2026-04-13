#pragma once
#include "Entity.h"

class Enemy : public Entity
{
private:
	//Variables
	std::vector<Entity*>* targets;

	//Logic Variables
	float sightRange;
	float attackRange;
	float attackDuration;

	//Combat Logic
	bool isAttacking;
	bool isGotHit;

	float attackCooldown;
	float attackCooldownMax;

	//Spawn Logic variables
	bool isSpawning;
	float spawnTimer;
	float spawnDuration;
	short spawnDirection;

	//Patrol Logic variables
	float idleTimer;
	float idleTimerMax;
	int idleDirection;


	//Color
	sf::Color reastartColor;

	//Initializer functions
	void initVariables();
	void initComponents();
	void initAnimations();

	//Logic Helpers
	bool shouldAttack(Entity* target);
	void updatePatrolLogic(const float& dt);

public:
	Enemy(float x, float y, sf::Texture& texture_sheet, std::vector<Entity*>* targets);
	virtual ~Enemy();

	//Functions
	void spawnOnMap(short direction, float duration = 2.f); // Call this to make the enemy walk into the scene
	void update(const float& dt) override;
	void updateAnimation(const float& dt);
	void updateAI(const float& dt);

	//Accessors
	bool IsAttack() const { return this->isAttacking; }
	bool IsGotHit() const { return this->isGotHit; }

	//External events
	void gotHitEffect(const Entity& other, float force);
};