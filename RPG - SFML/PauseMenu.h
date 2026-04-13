#pragma once
#include  "GUI.h"
#include "LayerManager.h"

class PauseMenu 
	: public Obj
{
private:
	//Variables
	sf::RectangleShape blackScreen;
	sf::Sprite background;
	sf::Texture backgroundTexture; 
	sf::Font& font;
	sf::Text pauseTitle;
	LayerManager layerMangaer;


	std::map<std::string, gui::ButtonText*> buttons;

	//initialization
	void initVariables(sf::RenderWindow& window);
	void initButtons();


public:
	//constructors
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual~PauseMenu();

	//Accessors
	std::map<std::string, gui::ButtonText*> getButtons() const { return this->buttons; }

	//Methods
	bool update(const sf::Vector2f& mosPos);
	void addButton(const std::string& key, float x, float y, const std::string& text);
	bool isButtonPressed(const std::string& key) const;
	void render(sf::RenderTarget& target);
	bool isMouseOver(const sf::Vector2f& mousePos) override;
	void reset() override;

private:
	void updateButtons(const sf::Vector2f& mosPos);
};

