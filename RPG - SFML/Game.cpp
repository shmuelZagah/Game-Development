#include "stdafx.h"
#include "Game.h"
#include "Keyboard.h"

//--------------------------
// Game class implementation
//---------------------------

//Static Methods


void Game::initVariables()
{
	//Initialize variables
	this->window = nullptr;
	this->dt = 0.f;			//delta time
	gridSizeF = 64.f;	//->//mast be a positiv number | the size of every block in the grid
}

void Game::initGraphicsSettings()
{
	this->graphicsSettings.loadFromFile("Config/graphics.ini");
}

//Initialize Function
void Game::initWindow()
{
	GraphicsSettings* gfxS = &this->graphicsSettings;
	if (gfxS->fullscreen)
		this->window = new sf::RenderWindow(gfxS->resulution, gfxS->title, sf::Style::Fullscreen, gfxS->contextSettings);
	else
		this->window = new sf::RenderWindow(gfxS->resulution, gfxS->title, sf::Style::Titlebar | sf::Style::Close, gfxS->contextSettings);

	this->window->setFramerateLimit(gfxS->framerateLimit); //Set the framerate limit
	this->window->setVerticalSyncEnabled(gfxS->verticalSync); //Disable vertical sync
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supportedKeys.ini");

	std::string key = "";
	std::int16_t key_value = 0;

	//Read the keys from the file
	if (ifs.is_open()) {

		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}

	ifs.close();
}

void Game::initStateData()
{
	this->sd.window = this->window;
	this->sd.states = &this->states;
	this->sd.gfxS = &this->graphicsSettings;
	this->sd.supportedKeys = &this->supportedKeys;
	this->sd.gridSizeF = this->gridSizeF;
}

void Game::initStates()
{
	this->states.push(new MainMenuState(this->sd));
}


void Game::initMouse()
{
	this->mouse = new Mouse(*window);
	this->mouse->setGridSizeU(static_cast<unsigned>(this->gridSizeF));
}







//---constructors and destructors---\\

Game::Game()
{
	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow();
	this->initKeys();
	this->initStateData();
	this->initStates();
	this->initMouse();
}

Game::~Game()
{
	delete this->window;
	delete this->mouse;

	//Delete all states
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}


//------Methods------\\


void Game::endApplication()
{

}

void Game::update()
{
	this->mouse->update(*this->window);
	this->updateSFMLEvents();
	

	if (!states.empty())
	{
		this->states.top()->update(dt);

		if (this->states.top()->hasQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	//App end
	else
	{
		window->close();
		this->endApplication();
	}

	Keybord::update(); //Update the keyboard state
	/*this->mouse->update(*this->window);*/ //if want to update the mouse after all, make every click in dilay

}


void Game::run()
{
	while (this->window->isOpen())
	{
		updateDt(); //Update the delta time
		this->update();
		this->render();
	}
}



void Game::render()
{
	this->window->clear();

	//render item
	if (!states.empty())
		this->states.top()->render();

	//mouse render || grafics + information
	this->mouse->render(*window);

	//render game
	this->window->display();
}




//_______________________________\\

void Game::updateDt()
{
	//Update the delta time evry frame
	this->dt = dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
			this->window->close();
	}
}

