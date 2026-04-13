#pragma once

class Mouse {

public:
	enum key
	{
		Left,Right
	};

public:
	Mouse(sf::RenderWindow& window);

	//Accessors
	//static bool isMouseJustReleased();
	static bool isMouseJustReleased(Mouse::key);

	//Function
	bool loadTexture();
	void setGridSizeU(unsigned gridSizeU);


	void update(const sf::RenderWindow& window);

	void render(sf::RenderTarget& target);


private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Font font;
	sf::Text positionText;
	unsigned gridSizeU;

	bool isPressingLeft;
	bool isPressingRight;

	//Functions
	void updatePosXy(sf::Vector2f&);
	void updateMouseJustReleased(); 



	//Variables\\

	static bool isRelesedLeft;
	static bool isRelesedRight;
};


