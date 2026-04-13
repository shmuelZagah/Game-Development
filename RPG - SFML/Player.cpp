#include "stdafx.h"
#include "Player.h"

//--------------------------
// Player class implementation
//---------------------------

// Initializer functions\\

void Player::initVariables()
{
	isAttacking = false;
}

void Player::initComponents()
{
	this->CreateMovementComponent(300.f, 30.f, 5.f);
	this->CreateDamageComponent("ATTACK", 25);
	this->CreateHealthComponent(150.f, 150.f);
	this->CreateHitboxComponent({ 0,-50 }, { 30,80 });
	this->CreateHealthBar();
}


// constructor | destructor\\

Player::Player(float x, float y, sf::Texture& texture_sheet) : Entity()
{
	this->initVariables();
	this->setTexture(texture_sheet);

	this->CreateAnimationComponent(texture_sheet);

	int frameWidth = 256;
	int frameHight = 256;
	this->animationComponent->addAnimtion("IDLE", 0, 0, 19, 0, frameWidth, frameHight, 7.f);
	this->animationComponent->addAnimtion("KNOCKBACK", 0, 0, 19, 0, frameWidth, frameHight, 7.f, 2);
	this->animationComponent->addAnimtion("MOVE", 0, 1, 19, 1, frameWidth, frameHight, 4.f);
	this->animationComponent->addAnimtion("ATTACK", 0, 3, 19, 3, frameWidth, frameHight, 4.f, 1);
	sprite.setOrigin(frameWidth / 2, frameHight / 2);
	this->sprite.setPosition(x, y);

	this->initComponents();

}

Player::~Player()
{
}

void Player::update(const float& dt)
{
	Entity::update(dt);

	this->updateAnmation(dt);
}

void Player::updateAnmation(const float& dt)
{
	if (this->movementComponent->getState(MovementState::KNOCKBACK) && this->movementComponent->getVelocity().x != 0)
	{
		this->animationComponent->play("KNOCKBACK", dt);
	}
	else
	{
		this->sprite.setColor(sf::Color::White);
		this->movementComponent->stopKnockback();
		this->isGotHit = false;


		if (this->IsAttack())
		{
			this->animationComponent->play("ATTACK", true, dt);
			if (this->animationComponent->isDone("ATTACK")) this->isAttacking = false;
		}

		if (this->movementComponent->getState(MovementState::IDLE))
			this->animationComponent->play("IDLE", dt);

		if (this->movementComponent->getState(MovementState::RIGHT))
		{
			sprite.setScale(1, 1);
			this->animationComponent->play("MOVE", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
		}
		if (this->movementComponent->getState(MovementState::LEFT))
		{
			sprite.setScale(-1, 1);
			this->animationComponent->play("MOVE", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
		}
		if (this->movementComponent->getState(MovementState::UP) || this->movementComponent->getState(MovementState::DOWN))
		{
			this->animationComponent->play("MOVE", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
		}
	}

}

void Player::gotHitEffect(const Entity& other, float force)
{
	this->isAttacking = false;
	this->isGotHit = true;
	this->movementComponent->knockbackFrom(other.GetHitBoxBounds(), force);
	this->sprite.setColor(sf::Color::Red);
}


