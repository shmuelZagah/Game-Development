#pragma once
class GraphicsSettings
{
public:
	GraphicsSettings();

	//Variables
	std::string title; //Title of the game
	sf::VideoMode resulution; //Resolution of the game
	bool fullscreen; //Is the game fullscreen or not
	bool verticalSync; //Is the vertical sync enabled or not
	unsigned framerateLimit; //Framerate limit of the game
	sf::ContextSettings contextSettings; //Context settings for the game
	std::vector<sf::VideoMode> videoModes; //Vector of video modes

	//Functions
	void loadFromFile(const std::string path);
	void saveToFile(const std::string path);
};

