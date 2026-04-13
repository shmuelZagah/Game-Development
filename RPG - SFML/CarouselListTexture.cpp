#include "stdafx.h"
#include "CarouselListTexture.h"

gui::CarouselListTexture::CarouselListTexture(const sf::Vector2f& pos
	, const sf::Texture& textur, unsigned showPictur, unsigned numOfPicturs, unsigned sizeOfPictur)
	:sheet(const_cast<sf::Texture&>(textur)), texturRect(0, 0, sizeOfPictur, sizeOfPictur),
	activeTexturRect(0, 0, sizeOfPictur, sizeOfPictur), showPictur(showPictur), maxId(numOfPicturs - 1)
{
	currentId = 0;

	for (unsigned i = 0; i < numOfPicturs; i++)
	{
		this->buttons.push_back(new Button(pos.x + i * sizeOfPictur * 1.5, pos.y, sizeOfPictur, sizeOfPictur));
		this->buttons[i]->setTextur(this->sheet);
		this->buttons[i]->setTexturRect(this->texturRect);
		this->buttons[i]->setId(i);
		this->texturRect.left += sizeOfPictur;
		if (this->texturRect.left >= sheet.getSize().x)
		{
			this->texturRect.left = 0;
			this->texturRect.top += sizeOfPictur;
		}
	}

	this->next = new gui::ButtonArrow(pos.x + sizeOfPictur * 1.5 * showPictur, pos.y, sizeOfPictur / 2, sizeOfPictur / 2);
	this->next->rotate(90);
	this->previous = new gui::ButtonArrow(pos.x - sizeOfPictur * 1.5, pos.y, sizeOfPictur / 2, sizeOfPictur / 2);
	this->previous->rotate(-90);

	this->renderWindow.setSize(sf::Vector2f(sizeOfPictur * 1.5 * showPictur, sizeOfPictur * 1.5));
	this->renderWindow.setPosition(pos.x - (sizeOfPictur * 0.75), pos.y - sizeOfPictur * 0.75);
	this->renderWindow.setFillColor(sf::Color::White);
}


gui::CarouselListTexture::~CarouselListTexture()
{
	delete this->next;
	delete this->previous;
}

//Accessors
sf::IntRect gui::CarouselListTexture::getActiveTextureRect() const
{
	return this->activeTexturRect;
}


//Methods
bool gui::CarouselListTexture::update(const sf::Vector2f& mousePos)
{
	//If mouse not hover the list return false
	auto it = buttons.begin();
	if (!((this->renderWindow.getGlobalBounds().contains(mousePos))
		|| this->next->getGlobalBounds().contains(mousePos)
		|| this->previous->getGlobalBounds().contains(mousePos)))
		return false;
	
	//choose the active texture rectangle based on the button pressed
	for (auto& button : buttons)
	{
		if (!this->renderWindow.getGlobalBounds().contains(button->getGlobalBounds().left, button->getGlobalBounds().top)) continue;
		button->update(mousePos);
		if (button->isPressed())
		{
			int textureSize = this->activeTexturRect.width;
			int imagesPerRow = sheet.getSize().x / textureSize;

			int id = button->getId();

			int x = (id % imagesPerRow) * textureSize;
			int y = (id / imagesPerRow) * textureSize;

			this->activeTexturRect.left = x;
			this->activeTexturRect.top = y;
		}
	}

	this->next->update(mousePos);
	this->previous->update(mousePos);

	//update the active texture rectangle based on the next and previous buttons
	if (this->next->isPressed())
	{
		if (!((this->currentId + this->showPictur) > this->maxId))
		{
			this->currentId++;
			for (auto& but : buttons) {
				but->setPosition({ (float)(but->getPosition().x - but->getSize().x * 1.5),but->getPosition().y });
			}
		}
	}

	if (this->previous->isPressed())
	{
		if (this->currentId != 0)
		{
			this->currentId--;
			for (auto& but : buttons) {
				but->setPosition({ (float)(but->getPosition().x + but->getSize().x * 1.5),but->getPosition().y });
			}
		}
	}

	return true;
}

void gui::CarouselListTexture::render(sf::RenderTarget& target)
{
	//target.draw(this->renderWindow);
	for (auto& but : buttons)
	{
		if (this->renderWindow.getGlobalBounds().contains(but->getGlobalBounds().left, but->getGlobalBounds().top))
			but->render(target);
	}
	this->next->render(target);
	this->previous->render(target);

}