#pragma once
#include "State.h"

//-------------------------------------------
// Game MainMenuState 
//		main menu of the game (first page)
//		succesor of the State class
//-------------------------------------------


class MainMenuState :
	public State
{
private:
	//Variables
	sf::RectangleShape background;
	sf::Texture bgT; //background texture


	std::map<std::string, gui::ButtonText*> buttons;
	LayerManager layerManager; //manager for the buttons

	//Initialization functions
	void initVariables() override;
	void initBackground() override;
	void initKeybinds() override;
	void initButtons();

public:
	MainMenuState(StateData& sd);
	virtual ~MainMenuState();

	//Functions - Guides
	void endState();
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;


	//Functions - called
	void updateInpute(const float& dt);
	void updateButtons();
};

