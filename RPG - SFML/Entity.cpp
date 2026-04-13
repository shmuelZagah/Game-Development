#include "stdafx.h"
#include "Entity.h"

//--------------------------
// Entity class implementation
//---------------------------


//Initializer functions\\


void Entity::initVariables()
{
	this->hitboxComponent = nullptr;
	this->movementComponent = nullptr;
	this->animationComponent = nullptr;
	this->driveComponent = nullptr;
	this->rotationComponent = nullptr;
	this->healthComponent = nullptr;
	this->damageComponent = nullptr;
}


//constructor | destructor\\

Entity::Entity()
{
	initVariables();
}

Entity::~Entity()
{
	delete this->hitboxComponent;
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->driveComponent;
	delete this->rotationComponent;
	delete this->healthComponent;
	delete this->damageComponent;

	interactList.clear();
}




#pragma region  Component Methods

#pragma region Create
void Entity::CreateMovementComponent(const float maxVelocity, float accelertion, float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, accelertion, deceleration);
}

void Entity::CreateAnimationComponent(sf::Texture& texturSheets)
{
	this->animationComponent = new AnimationComponent(sprite, texturSheets);
}

void Entity::CreateHitboxComponent(sf::Vector2f offset, sf::Vector2f size)
{
	this->hitboxComponent = new HitboxComponent(this->sprite, offset.x, offset.y, size.x, size.y);
}

void Entity::CreateDriveComponent(const float maxVelocity, const float acceleration, const float deceleration, const float brakes)
{
	this->driveComponent = new DriveComponent(this->sprite, maxVelocity, acceleration, deceleration, brakes);
}

void Entity::CreateHealthComponent(const float health, const float maxHealth)
{
	this->healthComponent = new HealthComponent(health, maxHealth);
}

void Entity::CreateDamageComponent(std::string key, int damage)
{
	this->damageComponent = new DamageComponent(key, damage);
}

void Entity::CreateRotationComponent(const float maxSpeed, const float acceleration, const float deceleration)
{
	this->rotationComponent = new RotationComponent(this->sprite, maxSpeed, acceleration, deceleration);
}

#pragma endregion 

#pragma region interact

bool Entity::Interact(const Entity& other)
{
	if (this->hitboxComponent->checkIntersect(other.getBounds()) &&
		!std::any_of(this->interactList.begin(), this->interactList.end(), [&](const Entity* p) {return p == &other;}))
	{
		this->interactList.push_back(&other);
		return true;
	}
	else return false;
}

void Entity::InteractUpdate()
{
	for (auto it = interactList.begin(); it != interactList.end(); )
	{
		if (!this->hitboxComponent->checkIntersect((*it)->getBounds()))
		{
			it = interactList.erase(it);
		}
		else
		{
			++it;
		}
	}
}

#pragma endregion

void Entity::CreateHealthBar()
{

	sf::Vector2f offset = this->hitboxComponent->getOffsets();
	if (this->healthComponent)
		this->healthComponent->CreateHealthBar(this->sprite, -offset.x, -offset.y);
}

#pragma endregion


//Modefiers

void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
	sf::Vector2f temp(
		(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width) / 2,
		(sprite.getGlobalBounds().top + sprite.getGlobalBounds().height) / 2
	);
	sprite.setOrigin(temp);
}

void Entity::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}


//Main Methods\\

void Entity::move(MovementState state, const float& dt)
{
	//move only if the sprite exists
	if (movementComponent)
		this->movementComponent->move(state, dt);
}

void Entity::update(const float& dt)
{
	this->InteractUpdate();
	if (this->healthComponent)
		this->healthComponent->Update();
	if (this->movementComponent)
		this->movementComponent->update(dt);
	if (this->hitboxComponent)
		this->hitboxComponent->update();
}

void Entity::render(sf::RenderTarget& target)
{

	if (this->healthComponent && this->healthComponent->IsDead()) return;

	//render the sprite if it exists
	target.draw(this->sprite);

	if (this->hitboxComponent)
		this->hitboxComponent->render(target);

	if (this->healthComponent)
		this->healthComponent->Render(target);
}