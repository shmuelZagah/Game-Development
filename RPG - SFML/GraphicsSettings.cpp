#include "stdafx.h"
#include "GraphicsSettings.h"
#include "TileMap.h"


//-------------------------------------------------
//	Graphics Setting class implementation 
//-------------------------------------------------

//constructor
GraphicsSettings::GraphicsSettings() {
	this->title = "Defult";
	this->resulution = sf::VideoMode::getDesktopMode();			//Default resolution is the desktop resolution
	this->fullscreen = false;									//Default is windowed mode
	this->verticalSync = false;									//Default is vertical sync disabled
	this->framerateLimit = 60;									//Default framerate limit
	this->contextSettings.antialiasingLevel = 0;				//Default context settings
	this->videoModes = sf::VideoMode::getFullscreenModes();		//Get all the video modes available
}


//Functions
void GraphicsSettings::loadFromFile(const std::string path)
{
	//Create a window 
	std::ifstream ifs(path);

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> this->resulution.width >> this->resulution.height;
		ifs >> this->fullscreen;
		ifs >> this->framerateLimit;
		ifs >> this->verticalSync;
		ifs >> contextSettings.antialiasingLevel;
		ifs.close();
	}
}

void GraphicsSettings::saveToFile(const std::string path)
{
	//Create a window 
	std::ofstream ofs(path);

	if (ofs.is_open())
	{
		ofs << title;
		ofs << this->resulution.width << this->resulution.height;
		ofs << this->fullscreen;
		ofs << this->framerateLimit;
		ofs << this->verticalSync;
		ofs << contextSettings.antialiasingLevel;
		ofs.close();
	}
}




