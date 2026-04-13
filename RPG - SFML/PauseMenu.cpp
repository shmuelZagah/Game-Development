#include "stdafx.h"
#include "PauseMenu.h"

//initialization\\

void PauseMenu::initVariables(sf::RenderWindow& window)
{
	//Initialize the background

	//make the background darker
	this->blackScreen.setSize(sf::Vector2f{ static_cast<float>(window.getSize().x),static_cast<float>(window.getSize().y) });
	this->blackScreen.setFillColor(sf::Color(0, 0, 0, 150));

	//creat the window to work with
	this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/pauseMenu.png");
	this->background.setTexture(this->backgroundTexture);

	this->background.setOrigin(
		(this->background.getGlobalBounds().left + this->background.getGlobalBounds().width) / 2,
		(this->background.getGlobalBounds().top + this->background.getGlobalBounds().height) / 2);

	this->background.setPosition(
		window.getSize().x / 2.f,
		window.getSize().y / 2.5f
	);

	//Initialize the pause title
	this->pauseTitle.setFont(font);
	this->pauseTitle.setString("Pause");
	this->pauseTitle.setCharacterSize(30);
	this->pauseTitle.setOrigin(
		this->pauseTitle.getGlobalBounds().width / 2.f,
		this->pauseTitle.getGlobalBounds().height / 2.f
	);
	this->pauseTitle.setPosition(this->background.getPosition().x, 60);
	this->pauseTitle.setFillColor(sf::Color(255, 255, 255, 120));

}



//constructors\\

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font) : font(font)
{
	this->initVariables(window);
}

PauseMenu::~PauseMenu()
{
	for (auto& pair : buttons)
	{
		delete pair.second;
	}
	this->buttons.clear();
}




//Methods\\

bool PauseMenu::update(const sf::Vector2f& mosPos)
{
	if (!background.getGlobalBounds().contains(mosPos)) return false;

	layerMangaer.updateAll(mosPos);

	updateButtons(mosPos);
	return true;
}

void PauseMenu::updateButtons(const sf::Vector2f& mosPos)
{
	//Update the buttons


}

void PauseMenu::addButton(const std::string& key, float x, float y, const std::string& text)
{
	auto btn = std::make_unique<gui::ButtonText>(x, y,
		this->background.getGlobalBounds().width / 1.5, 70,
		text, &font, sf::Color(30, 0, 0, 0), sf::Color(50, 0, 30, 0), sf::Color(80, 0, 40, 0),
		sf::Color(250, 250, 250, 140), sf::Color(200, 200, 200, 100), sf::Color(200, 200, 200, 100));

	this->buttons[key] = btn.get();
	this->buttons[key]->reset();
	layerMangaer.addObj("key", std::move(btn));
}

bool PauseMenu::isButtonPressed(const std::string& key) const
{

	auto it = this->buttons.find(key);
	if (it != this->buttons.end())
		return it->second->isPressed();
	return false;

}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->blackScreen);
	target.draw(this->background);
	layerMangaer.renderAll(target);
	target.draw(this->pauseTitle);
}

bool PauseMenu::isMouseOver(const sf::Vector2f& mousePos)
{
	return this->background.getGlobalBounds().contains(mousePos);
}

void PauseMenu::reset()
{
	for (auto& pair : buttons)
		pair.second->reset();
}
