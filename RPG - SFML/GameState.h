#pragma once
#include "State.h"
#include "Player.h"
#include "TileMap.h"
#include "Enemy.h"

//----------------------------------------------
// Game GameState 
//		game state of the game
// 		contains the game logic in the main game
//		succesor of the State class
//----------------------------------------------


class GameState :
    public State
{
private:
	//Variables
	PauseMenu* pausedMenu;
	bool pausedGame;		 //true = when the game just got paused
	TileMap* tileMap;		 // Tile map for the game


	//Variables for test
	std::vector<Entity*> playersAsTargetForEnemy;
	std::vector<Player*> players;
	sf::CircleShape portal;
	float portalTimer = 0.f;
	float potalMaxTimer = 3.f;


	//Enemies
	std::vector<Enemy*> enemies;

	//Initialization functions
	void initBackground() override;
	void initKeybinds() override;
	void initTextures();
	void initPlayers();
	void initVariables() override;
	void initPauseMenu();
	void initTileMap();
	void initEnemies();
	

public:
	GameState(StateData& sd);
	virtual ~GameState();

	//Functions
	void endState(); 
	void update(const float& dt) override;
	void updatePlayerInpute(const float& dt);
	void updateInpute(const float& dt);
	void updateButtons();
	void updateEnemiesAndCombat(const float& dt);
	void render(sf::RenderTarget* target = nullptr) override;
};