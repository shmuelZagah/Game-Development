#pragma once
#include <iostream>

template <class T>
class ColorEditor
{
private:
	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	ColorEditor(sf::Color idle, sf::Color hover, sf::Color active)
		: idleColor(idle), hoverColor(hover), activeColor(active) {
	}
	T& setIdle(const sf::Color& idle) {
		this->idleColor = idle;
		return static_cast<T&>(*this);
	}

	T& setHover(const sf::Color& hover) {
		this->hoverColor = hover;
		return static_cast<T&>(*this);
	}

	T& setActive(const sf::Color& active) {
		this->activeColor = active;
		return static_cast<T&>(*this);
	}

	void setColor(sf::Color color);

	T& copy(const T& other);

	const sf::Color& getIdle() const { return this->idleColor; }
	const sf::Color& getHover() const { return this->hoverColor; }
	const sf::Color& getActive() const { return this->activeColor; }

	T& operator=(const T&) = delete;
};

template<class T>
inline void ColorEditor<T>::setColor(sf::Color color)
{
	this->setIdle(color);
	this->setHover(color);
	this->setActive(color);
}

template<class T>
inline T& ColorEditor<T>::copy(const T& other)
{
	this->idleColor = other.getIdle();
	this->hoverColor = other.getHover();
	this->activeColor = other.getActive();
}

class k : public ColorEditor<k> { using ColorEditor::ColorEditor; };
