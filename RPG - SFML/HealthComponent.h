#pragma once

class HealthBar;

class HealthComponent
{
private:
	//Variables
	float health;
	float maxHealth;

	//in future add health bar
	std::unique_ptr<HealthBar> healthBar;

public:
	HealthComponent(float health, float maxHealth = 0);
	virtual ~HealthComponent();

	//Modifiers
	void setHealth(float health);
	void resetToFullHealth();

	void hit(float dmg);
	void heal(float amount);

	void CreateHealthBar(sf::Sprite& sprite, float offset_x, float offset_y);

	//Accessors
	float GetHealth() const;
	float GetMaxHealth() const;
	bool IsDead() const;

	//Methods
	void Render(sf::RenderTarget& target);
	void Update();
};


class HealthBar
{
private:
	//Varibales
	sf::Vector2f offset;
	sf::RectangleShape healthBar;
	sf::RectangleShape healthBarOutline;
	sf::Texture* textur;
	sf::Sprite& sprite;


public:
	HealthBar(sf::Sprite& sprite, float offset_x, float offset_y);
	virtual ~HealthBar();

	void initHealthBarOutline();
	void initHealthBar();


	//Methods
	void Update(float currentHealth, float maxHealth);
	void Render(sf::RenderTarget& target);
};
