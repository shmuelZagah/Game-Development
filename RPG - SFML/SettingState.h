#pragma once
#include "State.h"
#include "LayerManager.h"

class SettingState :
    public State
{
private:
	//Variables
	sf::RectangleShape background;
	sf::Texture bgT;	//background texture
	sf::Texture arB;	//Arrow button

	std::map<std::string, gui::ButtonText*> buttons;
	std::map<std::string, gui::DropDownList*>  dropDownLists;
	std::map<std::string, gui::CarouselList*>  carouselLists;

	std::vector<sf::VideoMode> modes;

	std::vector<sf::Text> titleText;
	LayerManager layerManager;
	
	//Initialization functions
	void initVariables() override;
	void initBackground() override;
	void initKeybinds() override;
	void initGui();
	void initText();

public:

	//constructor
    SettingState(StateData& sd);
	virtual ~SettingState();

	//Methods - Guides
	void endState();
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;

	//Methods - called
	void updateInpute(const float& dt);
	void updateGui(const float& dt);
	void renderGui(sf::RenderTarget& target);
};

