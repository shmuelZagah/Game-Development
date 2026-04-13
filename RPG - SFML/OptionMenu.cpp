#include "stdafx.h"
#include "OptionMenu.h"

gui::OptionMenu::OptionMenu(float sizeX, float sizeY, float posX, float posY)
{
	this->optionMenuBk.setSize(sf::Vector2f(sizeX, sizeY));
	this->optionMenuBk.setPosition(posX, posY);
}

gui::OptionMenu::~OptionMenu()
{
	for (auto menu : this->optionMenus)
		delete menu.second;
}

void gui::OptionMenu::setBkFillColor(sf::Color color)
{
	this->optionMenuBk.setFillColor(color);
}

void gui::OptionMenu::createMenu(std::string name,gui::menuHoldList* menu)
{
	this->optionMenus[name] = menu;
}

void gui::OptionMenu::createTexturList(std::string key, gui::CarouselListTexture* texturList)
{
	this->texturLists[key] = (texturList);
}

gui::menuHoldList& gui::OptionMenu::getMenu(std::string key)
{
	return *this->optionMenus[key];
}

gui::CarouselListTexture& gui::OptionMenu::getTextureList(std::string key)
{
	return *this->texturLists[key];
}

//----------------------------------------
//			Obj implementation
//----------------------------------------

bool gui::OptionMenu::update(const sf::Vector2f& mousePos)
{
	if (!this->isMouseOver(mousePos)) return false;

	for (auto menu: this->optionMenus)
	{
		menu.second->update(mousePos);
	}
	for (auto texturList : this->texturLists)
	{
		texturList.second->update(mousePos);
	}
	
	return true;
}

void gui::OptionMenu::render(sf::RenderTarget& target)
{
	target.draw(this->optionMenuBk);
	for(auto menu: this->optionMenus)
	{ 
		menu.second->render(target);
		texturLists[menu.first]->render(target);
	}
}

bool gui::OptionMenu::isMouseOver(const sf::Vector2f& mousePos)
{
	if(!this->optionMenuBk.getGlobalBounds().contains(mousePos))
		return false;
	return  true;
}

void gui::OptionMenu::reset()
{

}
