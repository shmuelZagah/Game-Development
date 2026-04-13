#include "stdafx.h"
#include "EditorState.h"
#include "GameState.h"


//------------------------------------
// EditorState class implementation
//------------------------------------


	//initialization\\
//----------------------\\

void EditorState::initVariables()
{

}

void EditorState::initBackground()
{

}

void EditorState::initPauseMenu()
{
	this->pausedMenu = new PauseMenu(*this->sd->window, font);
	int i = 75;
	int y = 200;
	this->pausedMenu->addButton("RESUME_BTN", this->window->getSize().x / 2.f, this->window->getSize().y / 2.f - y, "Resume");
	this->pausedMenu->addButton("SAVE_BTN", this->window->getSize().x / 2.f, this->window->getSize().y / 2.f - y+i, "Save");
	this->pausedMenu->addButton("LOAD_BTN", this->window->getSize().x / 2.f, this->window->getSize().y / 2.f - y + i * 2, "Load");
	this->pausedMenu->addButton("EXIT_BTN", this->window->getSize().x / 2.f, this->window->getSize().y / 2.f - y + i * 3, "Exit");

	for(auto& it: ((PauseMenu*)this->pausedMenu)->getButtons())
		it.second->TextColor().setIdle(sf::Color(255, 255, 255, 120));

	this->pausedMenu->reset();
}

void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/editorState_Keybinds.ini");

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



void EditorState::initButtons()
{
	auto btn = std::make_unique<gui::ButtonText>(100, 100, 200.f, 50.f,
		"Back", &this->font,
		sf::Color(30, 30, 30, 100), sf::Color(30, 30, 30, 255), sf::Color(30, 30, 30, 100),
		sf::Color(240, 240, 240, 255), sf::Color(255, 255, 255, 255), sf::Color(200, 255, 255, 255));

	this->layerManager.addObj("BACK_BTN", std::move(btn));
}

void EditorState::initTileMap()
{
	auto tm = std::make_unique<TileMap>(this->sd->gridSizeF,
		(this->window->getSize().x / this->sd->gridSizeF) + 1,
		(this->window->getSize().y / this->sd->gridSizeF) + 1);

	this->tileMap = tm.get();
	layerManager.addObj("Tile_Map", std::move(tm));
	layerManager.pushObjToBack("Tile_Map");
	this->tileMap->creatSelector(this->mousePosView);
	this->tileMap->setTexturSheet("Resources/Images/Tiles/Test/test.png");
}

void EditorState::initOptionMenu()
{
	auto om = std::make_unique<gui::OptionMenu>(
		static_cast<float>(this->sd->window->getSize().x),250.f,0.f,1080 - 250.f);
	this->optionMenu = om.get();
	this->optionMenu->setBkFillColor(sf::Color(30, 30, 30, 255));

	this->optionMenu->createMenu("Layers",new gui::menuHoldList(
		sf::Vector2f(150, 1080 - 200),
		sf::Vector2f(250.f, 50.f),
		{ "Layer1" }, /* "Layer2", "Layer3", "Layer4"*/
		1, 0, this->font, gui::menuHoldList::BOTTOM));

	this->optionMenu->getMenu("Layers").setListColor(sf::Color(80, 0, 20, 100), sf::Color(100, 100, 100, 255), sf::Color(50, 50, 50, 255),
		sf::Color(200, 200, 200, 255), sf::Color(220, 220, 220, 255), sf::Color(240, 240, 240, 255),
		sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255));

	//pos,size, texture, number of pictures, size of each picture
	this->optionMenu->createTexturList("Layers",new gui::CarouselListTexture(
		sf::Vector2f(650, 1080 - 125),
		*this->tileMap->getTextureSheet(), 6, 8, this->sd->gridSizeF));

	//this->texturList = new gui::CarouselListTextur(
	//	sf::Vector2f(650, 1080 - 125),
	//	*this->tileMap->getTextureSheet(), 6, 8, this->sd->gridSizeF);

	// After creating UI elements, register their hit-tests in the layerManager
	this->layerManager.addObj("Option_Menu", std::move(om));
}






//---//Constructors\\---\\
//----------------------\\

EditorState::EditorState(StateData& sd) :
	State(sd)
{
	this->initVariables();
	this->initBackground();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTileMap();
	this->initOptionMenu();
}


EditorState::~EditorState()
{

}





//---//Methods\\---\\
//------------------\\


//Methods - Guides\\

void EditorState::endState()
{
	State::endState(); //Call the endState function of the base class
}




void EditorState::update(const float& dt)
{
	this->updateMousePositions();

	if (this->isPaused) //pause update
	{
		this->pausedMenu->update(this->mousePosView);
		this->updatePauseMenu();
	}

	else if (!this->isPaused) //unpause update
	{
		this->layerManager.updateAll(this->mousePosView);
		this->updateInpute(dt);
	}

	
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->layerManager.renderAll(*target);
	
	if (this->isPaused)
	{
		this->pausedMenu->render(*target);
	}

	if (!this->isPaused)
	{

	}

}




//Methods - called\\

void EditorState::updateInpute(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keysbinds.at("ESC"))))
	{ 
		this->pausedState();
		layerManager.resetAll();	
	}

	this->updateEditor(dt);
}

void EditorState::updateButtons()
{
	//Exit
	
}


void EditorState::updateEditor(const float& dt)
{
	
	// Toggle the grid
	if (Keybord::justPressed(sf::Keyboard::G))
	{
		this->tileMap->toggleGrid();
	}

	// change the texture rectangle
	this->tileMap->setTextureRect(this->optionMenu->getTextureList("Layers").getActiveTextureRect());
}

void EditorState::updatePauseMenu()
{
	if (this->pausedMenu->isButtonPressed("RESUME_BTN"))
	{
		this->pausedMenu->reset();
		this->unPausedState();
	}
	if (this->pausedMenu->isButtonPressed("SAVE_BTN"))
	{
		this->tileMap->saveToFile("Resources/saves/save.stm");
	}
	if (this->pausedMenu->isButtonPressed("LOAD_BTN"))
	{
		this->tileMap->loadFromFile("Resources/saves/save.stm");
	}
	if (this->pausedMenu->isButtonPressed("EXIT_BTN"))
	{
		this->endState();
	}
}












