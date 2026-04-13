#include "stdafx.h"
#include "TileMap.h"



//Initialization
void TileMap::initVariables(float gridSizeF, unsigned width, unsigned height, int layers)
{
	//Initialize variables
	this->gridSizeF = gridSizeF;
	this->gridSizeU = static_cast<unsigned>(gridSizeF);
	this->layers = layers;
	this->mapSize = { width,height };
	this->texturRect = sf::IntRect(0, 0, this->gridSizeF, this->gridSizeF);

	//this->textureSheet.loadFromFile("Resources/Images/Tiles/Test/test.png");
}

void TileMap::initGrid()
{

	//Initialize the grid
	this->grid.resize(mapSize.x, std::vector<sf::RectangleShape>());
	for (int x = 0; x < mapSize.x; x++)
	{
		this->grid[x].resize(mapSize.y, sf::RectangleShape({ this->gridSizeF, this->gridSizeF }));
		for (int y = 0; y < mapSize.y; y++)
		{
			this->grid[x][y].setPosition(x * this->gridSizeF, y * this->gridSizeF);
			this->grid[x][y].setFillColor(sf::Color::Transparent);
			this->grid[x][y].setOutlineColor(sf::Color(150, 150, 150, 150));
			this->grid[x][y].setOutlineThickness(1.f);
		}
	}
}

void TileMap::initSelector(sf::Vector2f mousePos)
{
	this->showSelector = true;
	this->selector.setFillColor(sf::Color::White);
	this->selector.setPosition(mousePos.x + 50, mousePos.y + 15);
	this->selector.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
	this->selector.setOutlineColor(sf::Color::Red);
	this->selector.setOutlineThickness(1.f);
	this->selector.setTexture(&this->textureSheet);
	this->selector.setTextureRect(this->texturRect);
}

//constructor
TileMap::TileMap(float gridSizeF, unsigned width, unsigned height)
{
	this->initVariables(gridSizeF, width, height);
	this->initGrid();
	this->showGrid = true;

	//X_dir
	this->map.reserve(mapSize.x);
	for (int x = 0; x < mapSize.x; x++)
	{
		this->map.push_back(std::vector<std::vector<Tile*>>());

		//Y_dir
		this->map[x].reserve(mapSize.y);
		for (int y = 0; y < mapSize.y; y++)
		{
			this->map[x].push_back(std::vector<Tile*>());
			//Z_dir
			this->map[x][y].reserve(layers);
			for (int z = 0; z < layers; z++)
			{
				this->map[x][y].push_back(nullptr);
			}
		}
	}

}

TileMap::~TileMap()
{
	this->clearMap();
}




//Accessors
const sf::Texture* TileMap::getTextureSheet() const
{
	return &this->textureSheet;
}

void TileMap::creatSelector(sf::Vector2f mousePos)
{
	this->initSelector(mousePos);
}

void TileMap::setTextureRect(const sf::IntRect& rec)
{
	this->texturRect = rec;
}

void TileMap::setTexturSheet(std::string path)
{
	this->path = path;
	if (!textureSheet.loadFromFile(path))
		throw "ERROR : TileMap::setTexturSheet : cant load the file";
}



//Function
bool TileMap::update(const sf::Vector2f& mousePos) {



	this->mousePosGrid = sf::Vector2i{
		static_cast<int>(mousePos.x) / static_cast<int>(this->gridSizeF),
		static_cast<int>(mousePos.y) / static_cast<int>(this->gridSizeF) };

	this->updateSelector();

	if (!this->isMouseOver((sf::Vector2f)this->mousePosGrid)) return false;

	this->showSelector = true;

	// Add a tile - only when mouse not over UI
	if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
		|| Mouse::isMouseJustReleased(Mouse::Left)))
	{
		this->addTile(mousePosGrid.x, mousePosGrid.y, 0, this->texturRect);
	}

	// Remove a tile
	if ((sf::Mouse::isButtonPressed(sf::Mouse::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
		|| Mouse::isMouseJustReleased(Mouse::Right)))
	{
		this->removeTile(mousePosGrid.x, mousePosGrid.y, 0);
	}

	return true;
}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : this->map)
		for (auto& y : x)
			for (auto* z : y)
				if (z) // if the tile is not null
					z->render(target);

	if (showGrid)
		for (auto& x : this->grid)
			for (auto& y : x)
			{
				target.draw(y); // Draw the grid lines
			}

	if (showSelector)
		target.draw(this->selector);

}

bool TileMap::isMouseOver(const sf::Vector2f& mousePos)
{
	if (mapSize.x > mousePos.x && mapSize.y > mousePos.y && mousePos.x >= 0 && mousePos.y >= 0)
		return true;

	return false;
}

void TileMap::reset()
{
	this->showSelector = false;
}

void TileMap::updateSelector()
{
	this->selector.setTextureRect(this->texturRect);
	this->selector.setPosition(this->mousePosGrid.x * (int)this->gridSizeF, this->mousePosGrid.y * (int)this->gridSizeF);
}



void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& rec, Tile::TileTypes type)
{
	//Add a tile to the map at the specified grid position
	if (x < this->mapSize.x && x >= 0
		&& y < this->mapSize.y && y >= 0
		&& z < layers && z >= 0)
	{

		//Check if the tile already exists
		if (this->map[x][y][z]) delete this->map[x][y][z];

		this->map[x][y][z] = (new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, this->textureSheet, rec, type));
	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	//Remove a tile to the map at the specified grid position
	if (x < this->mapSize.x && x >= 0
		&& y < this->mapSize.y && y >= 0
		&& z < layers && z >= 0)
	{
		if (this->map[x][y][z]) delete this->map[x][y][z];
		this->map[x][y][z] = nullptr; // Set the pointer to null after deleting

		/*---Another way to remove a all layers---*/

		//Check if the tile already exists
		//for (int k = 0; k < layers;k++)
		//{
		//	if (this->map[x][y][k])
		//	{
		//		delete this->map[x][y][k];
		//		this->map[x][y][k] = nullptr; // Set the pointer to null after deleting
		//	}
		//}
	}
}




//---Effects---\\

void TileMap::toggleGrid()
{
	this->showGrid = !this->showGrid;
}

void TileMap::setGridShow(bool show)
{
	this->showGrid = show;
}





//--------------------------------------
//			Save and Load
//--------------------------------------

void TileMap::saveToFile(const std::string& path)
{

	//save format\\

	/*
	General :
	map size x,y
	grid size
	layers
	path

	Tails:
	pos (x,y,z)
	textur rec pos (x,y)
	collision
	type
	*/


	std::ofstream saveFile(path);

	if (!saveFile.is_open())
		saveFile.open(path);

	if (saveFile) {
		saveFile << this->mapSize.x << " " << this->mapSize.y << "\n"
			<< this->gridSizeU << "\n"
			<< this->layers << "\n"
			<< this->path << "\n";

		for (int x = 0; x < mapSize.x; x++)
		{
			for (int y = 0; y < mapSize.y; y++)
			{
				for (int z = 0; z < layers; z++)
				{
					if (map[x][y][z])
						saveFile << x << " " << y << " " << z << " " << map[x][y][z]->toString() << "\n";
				}
			}
		}
	}

	saveFile.close();

}

void TileMap::loadFromFile(const std::string& path)
{

	std::ifstream loadFile(path);

	if (!loadFile.is_open())
		loadFile.open(path);

	if (loadFile) {

		this->clearMap();

		//General variables
		sf::Vector2f size = { 0,0 };
		unsigned gridSize = 0;
		unsigned layer = 0;
		std::string path = "";


		//Tile variables
		unsigned x = 0, y = 0, z = 0;
		unsigned texterRecX = 0, texturRecY = 0;
		bool collision = false;
		short type = 0;

		loadFile >> size.x >> size.y >> gridSize >> layer >> path;

		this->initVariables(gridSize, size.x, size.y, layer);
		this->setTexturSheet(path);

		//X_dir
		this->map.reserve(mapSize.x);
		for (int x = 0; x < mapSize.x; x++)
		{
			this->map.push_back(std::vector<std::vector<Tile*>>());

			//Y_dir
			this->map[x].reserve(mapSize.y);
			for (int y = 0; y < mapSize.y; y++)
			{
				this->map[x].push_back(std::vector<Tile*>());
				//Z_dir
				this->map[x][y].reserve(layers);
				for (int z = 0; z < layers; z++)
				{
					this->map[x][y].push_back(nullptr);
				}
			}
		}

		while (loadFile >> x >> y >> z >> texterRecX >> texturRecY >> collision >> type)
		{
			//Create a new tile and add it to the map
			this->addTile(x, y, z, sf::IntRect(texterRecX, texturRecY, this->gridSizeU, this->gridSizeU), (Tile::TileTypes)type);
			map[x][y][z]->setCollision(collision);
		}
	}
	else
	{
		std::cout << "Error loading map from file: " << path << std::endl;
	}

	loadFile.close();
}



void TileMap::clearMap()
{
	for (int x = 0; x < mapSize.x; x++)
	{
		for (int y = 0; y < mapSize.y; y++)
		{
			for (int z = 0; z < layers; z++)
			{
				delete this->map[x][y][z];
				this->map[x][y][z] = nullptr;
			}
		}
	}
	this->map.clear();
}