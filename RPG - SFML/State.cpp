#include "stdafx.h"
#include "State.h"

//--------------------------
// State class implementation
//---------------------------


//Initialization functions\\

void State::initFonts()
{
	if (!this->font.loadFromFile("Fonts/CASTELAR.TTF")) {
		throw("ERROR::EDITOR_STATE::COULD NOT LOAD FONT");
	}
}

//constructors\\

State::State(StateData& sd)
	: supportedKeys(sd.supportedKeys), window(sd.window), quit(false), states(sd.states),
	gridSizeF(std::abs(sd.gridSizeF))
{
	this->sd = &sd;
	this->initFonts();
	this->isPaused = false;
}

State::~State()
{
}



//Methods\\

void State::updateMousePositions()
{
	//Update the mouse positions
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
	this->mousePosGrid = sf::Vector2u{
		static_cast<unsigned>(this->mousePosView.x) / static_cast<unsigned>(this->gridSizeF),
		static_cast<unsigned>(this->mousePosView.y) / static_cast<unsigned>(this->gridSizeF) };
}

void State::pausedState()
{
	isPaused = true;
}

void State::unPausedState()
{
	isPaused = false;
}


void State::endState()
{
	this->quit = true; //Set the quit flag to true to exit the state
}

//--------------------------
//StateData class implementation
//---------------------------

StateData::StateData()
{

}

StateData::~StateData()
{
	
}
