#include "stdafx.h"
#include "SettingState.h"


//------------------------------------
// SettingState class implementation
//------------------------------------


	//initialization\\
//----------------------\\

void SettingState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingState::initBackground()
{
	//Initialize the background
	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	if (!this->bgT.loadFromFile("Resources/Images/Backgrounds/Setting_State_backfground.jpg")) {
		throw ("ERROR::MAIN_MENU_STATE::COULD NOT LOAD BACKGROUND TEXTURE");
	}
	this->background.setTexture(&bgT);
}

void SettingState::initKeybinds()
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

void SettingState::initGui()
{
	std::string context[] = { "Apply", "Back" };
	std::string names[] = { "Apply_BTN", "Back_BTN" };
	int size = sizeof(context) / sizeof(context[0]);
	for (int i = 0; i < size; i++) {

		auto BTN = std::make_unique<gui::ButtonText>(window->getSize().x / 2, window->getSize().y / 2 + 245 + i*60, 200.f,  50.f,
			context[i], &this->font,
			sf::Color(30, 0, 0, 0), sf::Color(20, 20, 30, 0), sf::Color(20, 20, 40, 0),
			sf::Color(255, 255, 255, 255), sf::Color(50, 255, 255, 255), sf::Color(50, 200, 255, 255));

		this->buttons[names[i]] = BTN.get();
		layerManager.addObj(context[i], std::move(BTN));
	}
	std::vector<std::string> str_modes;
	for (auto& it : this->modes)
		str_modes.push_back(std::to_string(it.width) + 'x' + std::to_string(it.height));


	auto resulution = std::make_unique<gui::DropDownList>(
		sf::Vector2f(1150.f, 350.f),
		sf::Vector2f(225.f, 50.f),
		str_modes,
		str_modes.size(),
		0,
		this->font
	);
	auto fullscreen = std::make_unique<gui::DropDownList>(
		sf::Vector2f{ 1150.f, 425.f },
		sf::Vector2f{ 225.f, 50.f },
		std::vector<std::string>{"on", "off"},
		2, 0, this->font
	);

	this->dropDownLists["Resulution"] = resulution.get();
	this->dropDownLists["Fullscreen"] = fullscreen.get();

	layerManager.addObj("Fullscreen", std::move(fullscreen));
	layerManager.addObj("Resulution", std::move(resulution));

	if (!arB.loadFromFile("Resources/Images/Buttons/arrow.png")) throw "ERROR: couldnt load button arrow textur";

	for (auto& it : this->dropDownLists)
	{
		it.second->setListColor(
			sf::Color(20, 40, 50, 200), sf::Color(20, 20, 30, 150), sf::Color(20, 20, 40, 100),
			sf::Color(255, 255, 255, 255), sf::Color(50, 255, 255, 255), sf::Color(50, 200, 255, 255)
		);
		it.second->setActiveColor(sf::Color(20, 40, 50, 200), sf::Color(20, 20, 30, 150), sf::Color(20, 20, 40, 100),
			sf::Color(255, 255, 255, 255), sf::Color(50, 255, 255, 255), sf::Color(50, 200, 255, 255)
			,sf::Color::Black, sf::Color::Black, sf::Color::Black
		);
	}



	/*for (auto& it : this->carouselLists)
	{
		it.second->setListColor(
			sf::Color(0, 10, 10, 90), sf::Color(0, 10, 10, 90), sf::Color(0, 10, 10, 90),
			sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255),
			sf::Color::Black, sf::Color::Black, sf::Color::Black
		);
		it.second->setOutLineThickness(1.f);
		it.second->setArrowTextur(arB);
		it.second->next->BackgroundColor().setIdle(sf::Color(0, 100, 120, 255));
		it.second->back->BackgroundColor().setIdle(sf::Color(0, 100, 120, 255));
	}*/
}

void SettingState::initText()
{
	std::string text[] = { "RESULUTION","Fullscreen", "Vsync", "Antialiasing" };
	for (int i = 0; i < 4; i++)
	{
		this->titleText.push_back(sf::Text());
		this->titleText[i].setFont(this->font);
		this->titleText[i].setCharacterSize(30);
		this->titleText[i].setFillColor(sf::Color(205, 255, 255, 255));
		this->titleText[i].setString(text[i]);
		this->titleText[i].setOrigin(
			this->titleText[i].getGlobalBounds().left + this->titleText[i].getGlobalBounds().width,
			this->titleText[i].getGlobalBounds().top + this->titleText[i].getGlobalBounds().height / 2
		);
		this->titleText[i].setPosition(950, 350 + i * 75);


		/*this->titleText.setString("RESULUTION\n\nFullscreen\n\nVsync\n\nAntialiasing ");*/
	}
}




//Constructors\\


SettingState::SettingState(StateData& sd)
	: State(sd)
{
	this->initVariables();
	this->initBackground();
	this->initKeybinds();
	this->initGui();
	this->initText();
}


SettingState::~SettingState()
{

}





//Methods\\
//---------------\\

//Methods - Guides
void SettingState::endState()
{
	State::endState(); //Call the endState function of the base class
}

void SettingState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInpute(dt);
	layerManager.updateAll(this->mousePosView);
	this->updateGui(dt);

}

void SettingState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderGui(*target);

	for (auto& it : this->titleText)
		target->draw(it);
}



//Methods - called
void SettingState::updateInpute(const float& dt)
{

}

void SettingState::updateGui(const float& dt)
{
	if (buttons["Back_BTN"]->isPressed()) this->endState();
	
	if (buttons["Apply_BTN"]->isPressed()); //apply chang
}

void SettingState::renderGui(sf::RenderTarget& target)
{
	layerManager.renderAll(target);
}
