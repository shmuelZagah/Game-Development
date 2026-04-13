#pragma once
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"
#include "DriveComponent.h"
#include "RotationComponent.h"
#include "HealthComponent.h"
#include "DamageComponent.h"

//-------------------------------------------------
// Entity class
//		Base class for all the entities in the game
//--------------------------------------------------

class Entity
{
private:
	//Initializer functions
	void initVariables();

protected:

	//Variables
	sf::Sprite sprite;
	std::vector<const Entity*> interactList;

	//Components
	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	DriveComponent* driveComponent;
	RotationComponent* rotationComponent;
	HealthComponent* healthComponent;
	DamageComponent* damageComponent;

public:
	Entity();
	virtual ~Entity();

#pragma region components

	//Component create
	void CreateMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void CreateAnimationComponent(sf::Texture& texturSheets);
	/// <summary>
	/// sprite,offset.x offset.y, size.x, size.y
	/// </summary>
	void CreateHitboxComponent(sf::Vector2f, sf::Vector2f size);
	void CreateDriveComponent(const float maxVelocity, const float acceleration, const float deceleration, const float brakes = 10);
	void CreateHealthComponent(const float health, const float maxHealth = 0);
	void CreateDamageComponent(std::string key, int damage = 10);
	void CreateRotationComponent(const float maxSpeed, const float acceleration, const float deceleration);

	//Modifaiers to components
	void Hit(float dmg) { this->healthComponent->hit(dmg); }

	//Accessors
	sf::FloatRect GetHitBoxBounds() const { return this->hitboxComponent->getBounds(); }
	float GetDmg(std::string key) const { return this->damageComponent->getDamage(key);  }
	bool IsDead() const { if (this->healthComponent) return this->healthComponent->IsDead(); return false; }

	//Component Methods
	bool Interact(const Entity&);
	void InteractUpdate();
	void CreateHealthBar();

#pragma endregion

	//Modefiers
	void setPosition(const float x, const float y);
	void setTexture(sf::Texture& texture);
	sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }
	sf::Vector2f GetVelocity()const { return this->movementComponent->getVelocity(); }

	//Methods - Main Methods
	virtual void move(MovementState state, const float& dt);
	virtual void update(const float& dt);
	void render(sf::RenderTarget& target);
};

