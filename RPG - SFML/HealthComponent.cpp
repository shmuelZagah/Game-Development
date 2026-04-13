#include "stdafx.h"
#include "HealthComponent.h"



HealthComponent::HealthComponent(float health, float maxHealth) : health(health), healthBar(nullptr)
{

	this->maxHealth = (maxHealth <= 0 ? health : maxHealth);
}

HealthComponent::~HealthComponent()
{
}


//Methods\\

void HealthComponent::hit(float dmg)
{
	this->health -= dmg;
	if (this->health < 0)
		this->health = 0;
}

void HealthComponent::heal(float amount)
{
	this->health += amount;
	if (this->health > maxHealth)
		this->health = maxHealth;
}

void HealthComponent::CreateHealthBar(sf::Sprite& sprite, float offset_x, float offset_y)
{

	this->healthBar = std::make_unique<HealthBar>(sprite, offset_x, offset_y);
}

//Modifiers

void HealthComponent::setHealth(float health)
{
	this->health = health;
}

void HealthComponent::resetToFullHealth()
{
	this->health = maxHealth;
}

//Accessors

float HealthComponent::GetHealth() const
{
	return this->health;
}

float HealthComponent::GetMaxHealth() const
{
	return this->maxHealth;
}

bool HealthComponent::IsDead() const
{
	return this->health <= 0;
}

void HealthComponent::Render(sf::RenderTarget& target)
{
	if (this->healthBar)
		this->healthBar->Render(target);
}

void HealthComponent::Update()
{
	if (this->healthBar)
	{
		this->healthBar->Update(this->health, this->maxHealth);
	}

}







//==============================
#pragma region HealthBar class implementation
//==============================
HealthBar::HealthBar(sf::Sprite& sprite, float offset_x, float offset_y)
	: sprite(sprite)
{

	this->textur = nullptr;

	this->offset.x = sprite.getLocalBounds().left;
	this->offset.y = sprite.getLocalBounds().top - offset_y;

	this->initHealthBarOutline();
	this->initHealthBar();

}

HealthBar::~HealthBar()
{
	delete this->textur;
}



void HealthBar::Update(float currentHealth, float maxHealth)
{
	this->healthBarOutline.setPosition(this->sprite.getPosition().x + this->offset.x, this->sprite.getPosition().y + this->offset.y);
	this->healthBar.setPosition(this->healthBarOutline.getGlobalBounds().left + this->healthBarOutline.getOutlineThickness(), this->healthBarOutline.getPosition().y);

	float hpPercent = currentHealth / maxHealth;

	float maxWidth = this->healthBarOutline.getSize().x;
	this->healthBar.setSize(sf::Vector2f(maxWidth * hpPercent, this->healthBar.getSize().y));
	this->healthBar.setFillColor(sf::Color(255 * (1 - hpPercent * hpPercent), 255 * (hpPercent), 50, 255));
}

void HealthBar::Render(sf::RenderTarget& target) {
	target.draw(this->healthBar);
	target.draw(this->healthBarOutline);
}

//-----------------
#pragma region Init
//-----------------
void HealthBar::initHealthBarOutline()
{
	//Health bar outline
	this->healthBarOutline.setSize({ sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().width / 20 });
	this->healthBarOutline.setOutlineColor(sf::Color::Blue);
	this->healthBarOutline.setFillColor(sf::Color::Transparent);
	this->healthBarOutline.setOutlineThickness(2);
	this->healthBarOutline.setOrigin(
		(this->healthBarOutline.getGlobalBounds().left + this->healthBarOutline.getGlobalBounds().width) / 2,
		(this->healthBarOutline.getGlobalBounds().top + this->healthBarOutline.getGlobalBounds().height) / 2
	);
	this->healthBarOutline.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y);
}

void HealthBar::initHealthBar()
{

	//Health bar fill
	this->healthBar.setSize(this->healthBarOutline.getSize());
	this->healthBar.setFillColor(sf::Color::Green);
	this->healthBar.setOrigin(this->healthBar.getLocalBounds().left,
		(this->healthBar.getGlobalBounds().top + this->healthBar.getGlobalBounds().height) / 2);
	this->healthBar.setPosition(this->healthBarOutline.getGlobalBounds().left, this->healthBarOutline.getPosition().y);
}
#pragma endregion


//-----------------
#pragma endregion 
//==============================


