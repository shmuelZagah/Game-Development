#pragma once
#include "GameState.h"
#include "MainMenuState.h"
#include "Mouse.h"
#include <sstream>

//---------------------------------------------------
// Game class
//		main of the game
//		control all the objects and state in the game
//---------------------------------------------------


class Game
{
private:
	//Variables
	sf::RenderWindow *window;
	sf::Event event;
	Mouse* mouse;
	GraphicsSettings graphicsSettings; //Window settings
	StateData sd;
	float gridSizeF;


	sf::Clock dtClock;		//delta time clock
	float dt;				//delta time

	std::stack<State*> states;
	std::map<std:: string, int> supportedKeys; //Supported keys for the game

	//Initialize Function
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStateData();
	void initStates();
	void initMouse();

	
	
public:
	Game();
	virtual ~Game();
	//Static Methods


	//--Functions--\\
	
	//Methods
	void endApplication(); //didnt like maybe i will delete

	//update
	void updateDt();
	void update();
	void updateSFMLEvents();

	//render - and - runing
	void run();
	void render();
	
};

