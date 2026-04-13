#pragma once

//-------------------------------
// HitboxComponent class 
//--------------------------------

class HitboxComponent
{
private:
	//Varibales
	sf::Sprite& sprite;
	sf::RectangleShape hitBox;
	sf::Vector2f offset;

	//Health Bar
	sf::RectangleShape healthBar;
	sf::Texture textur;

public:
	HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	~HitboxComponent();

	//Accessors
	sf::FloatRect getBounds() const;
	sf::Vector2f getOffsets() const { return this->offset; }

	//Methods
	bool checkIntersect(const sf::FloatRect& frect);

	void update();
	void render(sf::RenderTarget& target);
};

