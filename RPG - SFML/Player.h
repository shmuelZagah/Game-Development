#pragma once
#include "Entity.h"


//-----------------------
// Player class
//-----------------------

class Player : public Entity
{
private:
	//Initializer functions
	void initVariables();
	void initComponents();

	//Variables
	bool isAttacking;
	bool isGotHit;



public:
	Player(float x, float y, sf::Texture& texture);
	virtual ~Player();

	//Methods
	virtual void update(const float& dt) override;
	void updateAnmation(const float& dt);
	void startAttack() { isAttacking = true; };
	bool IsAttack() { return isAttacking; }
	bool IsGotHit() { return isGotHit; }
	void gotHitEffect(const Entity& pusedFrom, float force);



};

