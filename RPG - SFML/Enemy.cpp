#include "stdafx.h"
#include "Enemy.h"

//---------------------------------------------------------
// Initializers
//---------------------------------------------------------

void Enemy::initVariables()
{
	this->sightRange = 400.f;
	this->attackDuration = 2.f;
	this->attackRange = 60.f;

	this->isAttacking = false;
	this->isGotHit = false;

	this->attackCooldownMax = 2.f;
	this->attackCooldown = this->attackCooldownMax;

	this->reastartColor = sf::Color(255, 100, 170, 255);

	// Spawn Logic
	this->isSpawning = false;
	this->spawnTimer = 0.f;
	this->spawnDuration = 0.f;
	this->spawnDirection = 0;

	// Patrol Logic
	this->idleTimer = 0.f;
	this->idleTimerMax = 1.0f; // Changes direction every ~1-3 seconds
	this->idleDirection = 0;
}

void Enemy::initComponents()
{
	// Max speed, acceleration, deceleration
	this->CreateMovementComponent(200.f, 30.f, 5.f);

	this->CreateHitboxComponent({ 0.f, -50.f }, { 30.f, 80.f });

	this->CreateHealthComponent(60, 60);
	this->CreateHealthBar();

	this->CreateDamageComponent("ATTACK", 20);
}

void Enemy::initAnimations()
{
	int width = 256;
	int height = 256;

	this->animationComponent->addAnimtion("IDLE", 0, 0, 19, 0, width, height, 7.f);
	this->animationComponent->addAnimtion("MOVE", 0, 1, 19, 1, width, height, 4.f);
	this->animationComponent->addAnimtion("ATTACK", 0, 3, 19, 3, width, height, 4.f, 1);
	this->animationComponent->addAnimtion("KNOCKBACK", 0, 0, 19, 0, width, height, 7.f, 2);
}

//---------------------------------------------------------
// Constructor / Destructor
//---------------------------------------------------------

Enemy::Enemy(float x, float y, sf::Texture& texture_sheet, std::vector<Entity*>* targets)
	: Entity(), targets(targets)
{
	this->initVariables();

	this->setPosition(x, y);
	this->setTexture(texture_sheet);

	this->CreateAnimationComponent(texture_sheet);
	this->initAnimations();

	this->sprite.setOrigin(128.f, 128.f);

	this->initComponents();
}

Enemy::~Enemy()
{
}

//---------------------------------------------------------
// Logic Functions
//---------------------------------------------------------

// Called externally to set initial walk direction
void Enemy::spawnOnMap(short direction, float duration)
{
	this->isSpawning = true;
	this->spawnDirection = direction;
	this->spawnDuration = duration;
	this->spawnTimer = 0.f;
}

// Internal logic for random movement when idle
void Enemy::updatePatrolLogic(const float& dt)
{
	this->idleTimer += dt;

	if (this->idleTimer >= this->idleTimerMax)
	{
		this->idleTimer = 0.f;
		this->idleDirection = rand() % 5; // 0=Idle, 1=Right, 2=Left, 3=Down, 4=Up
		this->idleTimerMax = (rand() % 3) + 1.f; // Random time between 1-4 seconds
	}

	switch (this->idleDirection)
	{
	case 1: this->move(MovementState::RIGHT, dt); break;
	case 2: this->move(MovementState::LEFT, dt); break;
	case 3: this->move(MovementState::DOWN, dt); break;
	case 4: this->move(MovementState::UP, dt); break;
	default: break; // Stand still
	}
}

bool Enemy::shouldAttack(Entity* target)
{
	sf::Vector2f velocity = this->movementComponent->getVelocity();
	float speed = std::sqrt(std::pow(velocity.x, 2) + std::pow(velocity.y, 2));

	if (speed < 10.f) return false;

	// Physics prediction
	float deceleration = 5.f;
	float timeToStop = speed / deceleration;
	float actualTime = std::min(this->attackDuration, timeToStop);
	float slideDistance = (speed * actualTime) - (0.5f * deceleration * std::pow(actualTime, 2));

	sf::Vector2f myPos = this->GetHitBoxBounds().getPosition();
	sf::Vector2f moveDir = velocity / speed;
	sf::Vector2f myFuturePos = myPos + (moveDir * slideDistance);

	sf::Vector2f targetPos = target->GetHitBoxBounds().getPosition();
	sf::Vector2f targetVel = target->GetVelocity();
	sf::Vector2f targetFuturePos = targetPos + (targetVel * actualTime);

	// Direction check
	sf::Vector2f dirToTarget = targetPos - myPos;
	float distToTarget = std::sqrt(std::pow(dirToTarget.x, 2) + std::pow(dirToTarget.y, 2));
	if (distToTarget > 0) dirToTarget /= distToTarget;

	float dotProduct = (moveDir.x * dirToTarget.x) + (moveDir.y * dirToTarget.y);
	if (dotProduct < 0.5f) return false;

	// Collision prediction
	sf::FloatRect myFutureRect = this->GetHitBoxBounds();
	myFutureRect.left = myFuturePos.x;
	myFutureRect.top = myFuturePos.y;

	sf::FloatRect targetFutureRect = target->GetHitBoxBounds();
	targetFutureRect.left = targetFuturePos.x;
	targetFutureRect.top = targetFuturePos.y;

	if (myFutureRect.intersects(targetFutureRect) || this->GetHitBoxBounds().intersects(target->GetHitBoxBounds()))
	{
		return true;
	}

	return false;
}

//---------------------------------------------------------
// Update Functions
//---------------------------------------------------------

void Enemy::gotHitEffect(const Entity& other, float force)
{
	this->isAttacking = false;
	this->isGotHit = true;

	this->movementComponent->knockbackFrom(other.GetHitBoxBounds(), force);
	this->sprite.setColor(sf::Color::Red);
}

void Enemy::updateAI(const float& dt)
{
	//if (this->targets->empty()) return;

	// Priority 1: Got Hit (Knockback)
	if (this->isGotHit) return;

	// Priority 2: Attacking (Sliding physics)
	if (this->isAttacking) return;

	// Priority 3: Spawning (Scripted movement)
	if (this->isSpawning)
	{
		this->spawnTimer += dt;
		if (this->spawnTimer >= this->spawnDuration)
		{
			this->isSpawning = false;
		}
		else
		{
			switch (this->spawnDirection)
			{
			case 1: this->move(MovementState::LEFT, dt); break;
			case 2: this->move(MovementState::RIGHT, dt); break;
			case 3: this->move(MovementState::UP, dt); break;
			case 4: this->move(MovementState::DOWN, dt); break;
			}
			return; // Skip other AI logic
		}
	}

	// Find Closest Target
	Entity* closestTarget = nullptr;
	float closestDistance = std::numeric_limits<float>::max();

	for (Entity* target : *this->targets)
	{
		sf::Vector2f targetPos = target->GetHitBoxBounds().getPosition();
		sf::Vector2f myPos = this->GetHitBoxBounds().getPosition();
		float distance = std::sqrt(std::pow(targetPos.x - myPos.x, 2) + std::pow(targetPos.y - myPos.y, 2));

		if (distance < closestDistance)
		{
			closestDistance = distance;
			closestTarget = target;
		}
	}

	if (!closestTarget) {
		this->updatePatrolLogic(dt); 
		return;
}

	sf::Vector2f myPos = this->GetHitBoxBounds().getPosition();
	sf::Vector2f targetPos = closestTarget->GetHitBoxBounds().getPosition();
	sf::Vector2f vecToCurrent = targetPos - myPos;
	float currentDistance = std::sqrt(std::pow(vecToCurrent.x, 2) + std::pow(vecToCurrent.y, 2));


	// Priority 4: Combat Decision
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		if (this->shouldAttack(closestTarget))
		{
			this->isAttacking = true;
			this->attackCooldown = 0.f;
			return; // Stop controlling movement
		}
	}

	// Priority 5: Chase Player
	if (currentDistance < this->sightRange)
	{
		sf::Vector2f dir = vecToCurrent / currentDistance;

		if (std::abs(vecToCurrent.x) > 20.f)
		{
			if (dir.x > 0) this->move(MovementState::RIGHT, dt);
			else this->move(MovementState::LEFT, dt);
		}

		if (std::abs(vecToCurrent.y) > 20.f)
		{
			if (dir.y > 0) this->move(MovementState::UP, dt);
			else this->move(MovementState::DOWN, dt);
		}
	}
	// Priority 6: Patrol (Random Movement)
	else
	{
		this->updatePatrolLogic(dt);
	}
}

void Enemy::updateAnimation(const float& dt)
{
	if (this->movementComponent->getState(MovementState::KNOCKBACK) && this->movementComponent->getVelocity().x != 0)
	{
		this->animationComponent->play("KNOCKBACK", dt);
	}
	else
	{
		this->sprite.setColor(this->reastartColor);
		this->movementComponent->stopKnockback();
		this->isGotHit = false;

		if (this->IsAttack())
		{
			this->animationComponent->play("ATTACK", true, dt);

			if (this->animationComponent->isDone("ATTACK"))
			{
				this->isAttacking = false;
			}
		}
		else if (this->movementComponent->getState(MovementState::IDLE))
		{
			this->animationComponent->play("IDLE", dt);
		}
		else if (this->movementComponent->getState(MovementState::RIGHT))
		{
			this->sprite.setScale(1, 1);
			this->animationComponent->play("MOVE", dt, std::abs(this->movementComponent->getVelocity().x), this->movementComponent->getMaxVelocity());
		}
		else if (this->movementComponent->getState(MovementState::LEFT))
		{
			this->sprite.setScale(-1, 1);
			this->animationComponent->play("MOVE", dt, std::abs(this->movementComponent->getVelocity().x), this->movementComponent->getMaxVelocity());
		}
		else if (this->movementComponent->getState(MovementState::UP) || this->movementComponent->getState(MovementState::DOWN))
		{
			this->animationComponent->play("MOVE", dt, std::abs(this->movementComponent->getVelocity().y), this->movementComponent->getMaxVelocity());
		}
	}
}

void Enemy::update(const float& dt)
{
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += dt;

	this->updateAI(dt);
	Entity::update(dt);
	this->updateAnimation(dt);
}