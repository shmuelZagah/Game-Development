#pragma once
#include "stdafx.h"
#include "Entity.h"
#include "GUI.h"
#include "PauseMenu.h"
#include "GraphicsSettings.h"
#include "TileMap.h"
#include "Keyboard.h"
#include "LayerManager.h" 
#include "Obj.h"

// Forward declaration
class PauseMenu; class Player; class TileMap;
class GraphicsSettings; class Entity;
class StateData;
class State;

//--------------------------------------------------
// Game State
//		Base class for all the states in the game
//		give the basic functionality for the states
//--------------------------------------------------



class StateData
{
public:
	//Variables
	float gridSizeF;
	sf::RenderWindow* window;
	GraphicsSettings* gfxS;
	std::map < std::string, int>* supportedKeys;
	std::stack<State*>* states;

	//Constructor
	StateData();
	~StateData();
};


class State
{
protected:
	StateData* sd;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keysbinds;
	bool quit;
	bool isPaused;
	float gridSizeF;

	sf::Font font;

	//Mouse
	sf::Vector2i mousePosScreen;	// Mouse position in the screen
	sf::Vector2i mousePosWindow;	// Mouse position in the window
	sf::Vector2f mousePosView;		// Mouse position in the view
	sf::Vector2u mousePosGrid;		// Mouse position in the grid

	//Resources
	std::map <std::string, sf::Texture*> textures;


	//Initialization functions
	virtual void initKeybinds() = 0;
	virtual void initBackground() = 0;
	void initFonts();
	virtual void initVariables() = 0;

public:
	State(StateData& sd); //sd -> state data
	virtual ~State();

	//Methods
	const bool& hasQuit() const { return this->quit; } // Check if the state should quit
	virtual void updateMousePositions(); // Update the mouse positions
	void pausedState();
	void unPausedState();

	//pure virtual functions
	virtual void endState(); // End the state
	virtual void updateInpute(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

