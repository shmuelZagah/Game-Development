#pragma once
#include "State.h"


//--------------------------------------------------
// EditorState State
//--------------------------------------------------



class EditorState :
    public State
{
private:
	//Variables
	PauseMenu* pausedMenu;
	TileMap* tileMap;		
	
	//Variables - buttons and controls
	gui::OptionMenu* optionMenu;

    LayerManager layerManager; //new manager for UI

	sf::Text positionOnGrid;

	//Initialization functions
	void initVariables() override;
	void initBackground() override;
	/*void initFonts();*/
	void initPauseMenu();
	void initKeybinds() override;
	void initOptionMenu();
	void initTileMap();
	void initButtons();
	

public:
	EditorState(StateData& sd);
	virtual ~EditorState();
	

	//Methods - Guides
	void endState();
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;


	//Methods - called
	void updateInpute(const float& dt);
	void updateButtons();
	void updateEditor(const float& dt);
	void updatePauseMenu();
};

