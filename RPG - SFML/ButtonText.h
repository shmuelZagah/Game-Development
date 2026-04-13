#pragma once
#include "Button.h"

namespace gui {

	class ButtonText
		: public Button
	{
	private:
		class EditorColorTX;

		//Variables
		sf::Font* font;
		sf::Text text;

		//Colors
		EditorColorTX* textColor;

		//initialization
		void initText(const std::string& text);

	public:
		ButtonText(float x, float y, float width, float hieght,
			std::string text, sf::Font* font,
			sf::Color idleColor = sf::Color::White,
			sf::Color hoverColor = sf::Color::White,
			sf::Color activeColor = sf::Color::White,
			sf::Color textIdleColor = { 200,200,200,200 },
			sf::Color textHoverColor = { 255, 255, 255, 255 },
			sf::Color textActiveColor = { 255, 255, 255, 200 },
			sf::Color outLineIdleColor = sf::Color::Transparent,
			sf::Color OutLineHoverColor = sf::Color::Transparent,
			sf::Color OutLineActiveColor = sf::Color::Transparent);


		ButtonText(const ButtonText& other);
		virtual ~ButtonText();


		//Accessors
		std::string getText() const;

		//Modifiers
		void setText(const std::string& text);
		void setPosition(const sf::Vector2f& pos) override;
		void setSize(float width, float hieght) override;


		//Color - Function
		void setColor(const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor,
			const sf::Color& textIdleColor, const sf::Color& textHoverColor, const sf::Color& textActiveColor,
			const sf::Color& outLineIdleColor = sf::Color::Transparent,
			const sf::Color& OutLineHoverColor = sf::Color::Transparent,
			const sf::Color& OutLineActiveColor = sf::Color::Transparent);

		void setTextColor(const sf::Color& textIdleColor, int = 30);

		//Functions
		//virtual void update(const sf::Vector2f& mousePos); -> dont need it right now
		virtual void render(sf::RenderTarget& target);

	private:
		//Private functions
		void updateColors();
		void restartTextOrigin();  //put the anchor of the text to the center of the buutton


	public:
		class EditorColorTX : public ColorEditor <EditorColorTX>
		{
			using ColorEditor::ColorEditor;
		};

		gui::ButtonText::EditorColorTX& TextColor();
	};
}
