#pragma once
#include "Tile.h"
#include "Obj.h"
#include "Mouse.h"

class TileMap
	: public Obj
{
private:

	//Variables
	float gridSizeF;
	sf::Vector2i mousePosGrid;		// Mouse position in the grid
	unsigned gridSizeU;
	unsigned layers;
	sf::Vector2u mapSize;
	std::vector<std::vector<std::vector<Tile*>>> map;
	std::vector<std::vector<sf::RectangleShape>> grid;
	std::string path;
	sf::Texture textureSheet;
	sf::IntRect texturRect;


	//Selector
	sf::RectangleShape selector;		// show the selected tile
	bool showSelector;

	//Effects
	bool showGrid; // Show the grid lines

	//Initialization
	void initVariables(float gridSizeF, unsigned width, unsigned height, int layers =5);
	void initGrid();
	void initSelector(sf::Vector2f mousePos);

	void clearMap();

public:
	TileMap(float gridSizeF, unsigned width, unsigned height);
	virtual ~TileMap();

	//Accessors
	const sf::Texture* getTextureSheet() const;

	//Modifiers
	void creatSelector(sf::Vector2f mousePos);
	void setTextureRect(const sf::IntRect& rec);
	void setTexturSheet(std::string path);


	//Function - called
	bool update(const sf::Vector2f& mousePos) override;
	void render(sf::RenderTarget& target) override;
	bool isMouseOver(const sf::Vector2f& mousePos) override;
	void reset() override; //reset for layer manager to idle state

	
	void updateSelector();


	//Methods
	void addTile(const unsigned x,const unsigned y, const unsigned z, const sf::IntRect& rec , Tile::TileTypes type = Tile::TileTypes::DEFAULT);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	//Effects
	void toggleGrid();
	void setGridShow(bool show);

	//save
	void saveToFile(const std::string& path);
	void loadFromFile(const std::string& path);
};




