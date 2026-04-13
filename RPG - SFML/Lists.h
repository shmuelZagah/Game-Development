#pragma once
#include "ButtonText.h"
#include "ButtonArrow.h"
#include "Mouse.h"
#include <vector>
#include "Obj.h"

class Lists : 
	public Obj
{

protected:

	//Variables
	gui::ButtonText* activeElement;
	std::vector<gui::ButtonText*> elementsList;

	sf::Font& font;

public:
	Lists(const sf::Vector2f& pos,const sf::Vector2f& size,const std::vector<std::string>& elements,
		unsigned short numOfElements, unsigned short defultIndex, sf::Font& font);

	virtual ~Lists();

	// Accessors
	sf::Vector2f getPosition() const;
	const unsigned short& getActiveId() const;

	//check if a point is over this list
	virtual bool containsPoint(const sf::Vector2f& point) const;


	//Modifiers
	void setActiveColor(const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor,
		const sf::Color& textIdleColor, const sf::Color& textHoverColor, const sf::Color& textActiveColor,
		const sf::Color& OLI = sf::Color::Transparent,
		const sf::Color& OLH = sf::Color::Transparent,
		const sf::Color& OLA = sf::Color::Transparent);

	virtual void setListColor(const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor,
		const sf::Color& textIdleColor, const sf::Color& textHoverColor, const sf::Color& textActiveColor,
		const sf::Color& OLI = sf::Color::Transparent,
		const sf::Color& OLH = sf::Color::Transparent,
		const sf::Color& OLA = sf::Color::Transparent);

	void setOutLineThickness(float thickness);
	virtual void setSize(float height, float width);


	//Methods
	virtual bool update(const sf::Vector2f& mousePos) override;
	virtual void render(sf::RenderTarget& target)override;
	virtual void reset()override;
	virtual bool isMouseOver(const sf::Vector2f& mousePos)override;

};

