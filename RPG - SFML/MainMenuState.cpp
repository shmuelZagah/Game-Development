#include "stdafx.h"
#include "MainMenuState.h"
#include "GameState.h"
#include "EditorState.h"
#include "SettingState.h"



//------------------------------------
// MainMenuState class implementation
//------------------------------------


	//initialization\\
//----------------------\\

void MainMenuState::initVariables()
{
}

void MainMenuState::initBackground()
{
	//Initialize the background
	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	if (!this->bgT.loadFromFile("Resources/Images/Backgrounds/main_menu_background.jpg")) {
		throw ("ERROR::MAIN_MENU_STATE::COULD NOT LOAD BACKGROUND TEXTURE");
	}
	this->background.setTexture(&bgT);
}

void MainMenuState::initKeybinds()
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

void MainMenuState::initButtons()
{
	std::string a[] = { "GameState_BTN","Setting_BTN","Edit_BTN","Exit_BTN"};
	std::string b[] = { "New Game","Setting","Edit","Exit"};
	for (int i = 0; i < 4; i++)
	{
		std::unique_ptr<gui::ButtonText> btnPtr = std::make_unique<gui::ButtonText>(
			window->getSize().x / 2.f, window->getSize().y / 2.f - 100.f + 90.f * i, 400.f, 100.f,
			b[i], &this->font,
			sf::Color(30, 0, 0, 0), sf::Color(80, 0, 20, 100), sf::Color(80, 0, 40, 100),
			sf::Color(230, 230, 255, 255), sf::Color(50, 255, 255, 255), sf::Color(50, 200, 255, 255));

		gui::ButtonText* rawPtr = btnPtr.get();
		this->layerManager.addObj(a[i], std::move(btnPtr));
		this->buttons[a[i]] = rawPtr;
	}
}




	//Constructors\\
//----------------------\\

MainMenuState::MainMenuState(StateData& sd)
	: State(sd)
{
	this->initVariables();
	this->initBackground();
	this->initKeybinds();
	this->initButtons();
}


MainMenuState::~MainMenuState()
{
	for (auto& pair : buttons)
	{
		delete pair.second;
	}
	this->buttons.clear();

}





//---//Methods\\---\\
//------------------\\

void MainMenuState::endState()
{
	State::endState(); //Call the endState function of the base class
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInpute(dt);
	this->layerManager.updateAll(this->mousePosView);	
	this->updateButtons();
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->layerManager.renderAll(*target);
}

void MainMenuState::updateInpute(const float& dt)
{

}

void MainMenuState::updateButtons()
{
	//New Game
	if (this->buttons.at("GameState_BTN")->isPressed())
	{
		states->push(new GameState(*this->sd));
	}

	//Setting
	if (this->buttons.at("Setting_BTN")->isPressed())
	{
		states->push(new SettingState(*this->sd));
	}


	//Editor
	if (this->buttons.at("Edit_BTN")->isPressed())
	{
		states->push(new EditorState(*this->sd));
	}

	//Exit
	if (this->buttons.at("Exit_BTN")->isPressed())
		this->endState();
}


