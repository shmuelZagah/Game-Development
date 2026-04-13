#pragma once

class Tile
{
public:
	enum TileTypes { DEFAULT =0, DAMAGING};

protected:
	sf::RectangleShape shape;
	bool collision;
	TileTypes type;


public:
	//constructor
	Tile();
	Tile(float x, float y, float gridSizeF, const sf::Texture& textur, const sf::IntRect& rec, TileTypes type = DEFAULT);
	virtual ~Tile();

	//Function
	void update();
	void render(sf::RenderTarget& target);

	//Methods
	const std::string toString();
	void setCollision(const bool collision);	
};

