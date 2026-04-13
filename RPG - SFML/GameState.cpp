#include "stdafx.h"
#include "GameState.h"

//--------------------------
// GameState class implementation
//---------------------------

//-----------------------------------------
#pragma region initialization functions
//-----------------------------------------
void GameState::initBackground()
{
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gameState_Keybinds.ini");

	std::string key = "";
	std::string fromKey = "";

	//Read the keys from the file
	if (ifs.is_open()) {

		while (ifs >> key >> fromKey)
		{
			this->keysbinds[key] = this->supportedKeys->at(fromKey);
		}
	}

	ifs.close();

	//Load keybinds from a file or set them manually
}

void GameState::initTextures()
{
	textures["PLAYER"] = new sf::Texture();
	textures["PLAYER"]->loadFromFile("Resources/Images/Player/sheets.png");

	textures["ENEMY"] = new sf::Texture();
	textures["ENEMY"]->loadFromFile("Resources/Images/Player/sheets.png");
}

void GameState::initPlayers()
{
	this->players.push_back(new Player(window->getSize().x / 2.f + 200, window->getSize().y / 2.f -100, *this->textures["PLAYER"]));
	this->players.push_back(new Player(window->getSize().x / 2.f +200, window->getSize().y / 2.f +100, *this->textures["PLAYER"]));

	for (auto& player : players)
		playersAsTargetForEnemy.push_back(player);
}

void GameState::initVariables()
{
	this->portal.setRadius(60);
	this->portal.setScale(1,2);
	this->portal.setFillColor(sf::Color(0, 50, 200, 255));
	this->portal.setOutlineColor(sf::Color(0,0,150,255));
	this->portal.setOutlineThickness(3);
	this->portal.setPosition(this->window->getSize().x- this->window->getSize().x*7/8,this->window->getSize().y/3);

	pausedGame = false;
}

void GameState::initPauseMenu()
{
	this->pausedMenu = new PauseMenu(*this->window, font);

	this->pausedMenu->addButton("RESUME_BTN", this->window->getSize().x / 2.f, this->window->getSize().y / 2.f - 215, "Resume");
	this->pausedMenu->addButton("SETTINGS_BTN", this->window->getSize().x / 2.f, this->window->getSize().y / 2.f - 120, "Settings");
	this->pausedMenu->addButton("SAVE_BTN", this->window->getSize().x / 2.f, this->window->getSize().y / 2.f - 25, "Save");
	this->pausedMenu->addButton("EXIT_BTN", this->window->getSize().x / 2.f, this->window->getSize().y / 2.f + 70, "Exit");

}

void GameState::initTileMap()
{
	//Initialize the tile map if needed
	this->tileMap = nullptr;
	//this->tileMap = new TileMap(this->sd->gridSizeF,
	//	(this->window->getSize().x / this->sd->gridSizeF) + 1,
	//	(this->window->getSize().y / this->sd->gridSizeF) + 1);
}

void GameState::initEnemies()
{
	this->enemies.push_back(new Enemy(600.f, 400.f, *this->textures["ENEMY"], &this->playersAsTargetForEnemy));
	this->enemies.push_back(new Enemy(200.f, 500.f, *textures["ENEMY"], &this->playersAsTargetForEnemy));
}

#pragma endregion
//-----------------------------------------

//constructor | destructor\\

GameState::GameState(StateData& sd)
	:State(sd)
{
	this->initVariables();
	this->initBackground();
	this->initKeybinds();
	this->initTextures();
	this->initPlayers();
	this->initEnemies();
	this->initPauseMenu();
	this->initTileMap();
}

GameState::~GameState()
{
	for (auto* player : players)
	{
		delete player;
	}

	this->playersAsTargetForEnemy.clear();

	delete this->tileMap;

	for (auto& enemy : this->enemies)
	{
		delete enemy;
	}
	this->enemies.clear();

	for (auto& item : this->textures)
	{
		delete item.second;
	}
	this->textures.clear();
}



//Functions\\

void GameState::endState()
{
	State::endState(); //Call the endState function of the base class
}

void GameState::update(const float& dt)
{

	this->updateMousePositions();
	this->updateInpute(dt);
	this->updateButtons();


	if (!this->isPaused) //Unpause update
	{
		//Update the game state
		this->updatePlayerInpute(dt);
		for (auto& player : players) player->update(dt);
		this->updateEnemiesAndCombat(dt);
	}
	if (this->isPaused)  //Pause update
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
			this->endState();
	}
}


void GameState::updatePlayerInpute(const float& dt)
{
	/*
	if (this->players[0]->IsAttack() && this->players[1]->Interact(*this->players[0]))
	{
		this->players[1]->Hit(this->players[0]->GetDmg("ATTACK"));
		this->players[1]->gotHitEffect(*this->players[0], 550);
	}

	if (this->players[1]->IsAttack() && this->players[0]->Interact(*this->players[1]))
	{
		this->players[0]->Hit(this->players[1]->GetDmg("ATTACK"));
		this->players[0]->gotHitEffect(*this->players[1], 550);
	}
	*/


	//Check for player 1 input
	if (!this->players[0]->IsAttack() && !this->players[0]->IsGotHit() && !this->players[0]->IsDead())
	{
		if (Keybord::justPressed(sf::Keyboard::Space))
			this->players[0]->startAttack();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keysbinds.at("MOVE_LEFT"))))
			this->players[0]->move(MovementState::LEFT, dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keysbinds.at("MOVE_RIGHT"))))
			this->players[0]->move(MovementState::RIGHT, dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keysbinds.at("MOVE_UP"))))
			this->players[0]->move(MovementState::DOWN, dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keysbinds.at("MOVE_DOWN"))))
			this->players[0]->move(MovementState::UP, dt);
	}

	//Check for player 2 input
	if (!this->players[1]->IsAttack() && !this->players[1]->IsGotHit() && !this->players[1]->IsDead())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			this->players[1]->move(MovementState::LEFT, dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			this->players[1]->move(MovementState::RIGHT, dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
			this->players[1]->move(MovementState::DOWN, dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
			this->players[1]->move(MovementState::UP, dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0))
			this->players[1]->startAttack();
	}

}

void GameState::updateInpute(const float& dt)
{
	//change the pause state || dont chang for long click
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keysbinds.at("ESC"))) && pausedGame == isPaused)
	{
		this->isPaused = !this->isPaused;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keysbinds.at("ESC")))) pausedGame = isPaused;
}

void GameState::updateButtons()
{
	if (this->isPaused)
	{
		this->pausedMenu->update(this->mousePosView);

		if (this->pausedMenu->isButtonPressed("EXIT_BTN"))
			this->endState();
		if (this->pausedMenu->isButtonPressed("RESUME_BTN"))
			this->isPaused = false;
	}
}

void GameState::updateEnemiesAndCombat(const float& dt)
{
	this->portalTimer += 1.f *dt;

	if (this->portalTimer >= this->potalMaxTimer)
	{
		portalTimer = 0;
		Enemy* temp = new Enemy(this->portal.getPosition().x + 120, this->portal.getPosition().y + 120, *this->textures["ENEMY"], &this->playersAsTargetForEnemy);
		temp->spawnOnMap(2, 1.5);
		this->enemies.push_back(temp);
	}

	for (int i = 0; i < this->enemies.size(); ++i)
	{
		Enemy* enemy = this->enemies[i];

		enemy->update(dt);

		//Enemy and Player combat check

		//Enemy got hit from player
		for (auto player : this->players)
		{
			if (player->IsAttack() && enemy->Interact(*player))
			{
				enemy->Hit(player->GetDmg("ATTACK"));
				enemy->gotHitEffect(*player, 550.f); 
			}
		}


		//Enemy attack
		for (int i = 0;i < this->players.size();i++)
		{
			if (enemy->IsAttack() && this->players[i]->Interact(*enemy))
			{
				if (!this->players[i]->IsGotHit())
				{
					this->players[i]->Hit(enemy->GetDmg("ATTACK"));
					this->players[i]->gotHitEffect(*enemy, 400.f);
					if (this->players[i]->IsDead())
					{
						Player* playerPtr = this->players[i];

						for (int j = 0; j < this->playersAsTargetForEnemy.size(); j++)
						{
							if (playersAsTargetForEnemy[j] == playerPtr)
							{				
								this->playersAsTargetForEnemy.erase(this->playersAsTargetForEnemy.begin() + j);
								break; 
							}
						}
						//delete this->players[i]; 
						//this->players.erase(this->players.begin() + i);
						--i; 
					}
				}
			}
		}

		if (this->enemies[i]->IsDead()) 
		{
			delete this->enemies[i];
			this->enemies.erase(this->enemies.begin() + i);
			--i; 
		}
	}
}


void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->portal);

	for (auto& player : this->players)
	{
		player->render(*target);
	}

	for (auto& enemy : this->enemies)
	{
		enemy->render(*target);
	}

	if (this->isPaused)
	{
		this->pausedMenu->render(*target);
	}
}


