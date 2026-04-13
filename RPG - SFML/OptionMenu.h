#pragma once
#include "Obj.h"
#include "GUI.h"

namespace gui {

	class OptionMenu
		: public Obj
	{

	private:
		sf::RectangleShape optionMenuBk;
		std::map<std::string, gui::menuHoldList*> optionMenus;
		std::map<std::string, gui::CarouselListTexture*> texturLists;

	public:
		OptionMenu(float sizeX, float sizeY, float posX, float posY);
		~OptionMenu();

		//Modifiers
		void setBkFillColor(sf::Color color);

		//Methods
		void createMenu(std::string key, gui::menuHoldList* menu);
		void createTexturList(std::string,gui::CarouselListTexture* texturList);


		//Accessors
		gui::menuHoldList& getMenu(std::string key);
		gui::CarouselListTexture& getTextureList(std::string key);



		virtual bool update(const sf::Vector2f& mousePos) override;
		virtual void render(sf::RenderTarget& target) override;
		virtual bool isMouseOver(const sf::Vector2f& mousePos) override;
		virtual void reset() override;



	};
}
