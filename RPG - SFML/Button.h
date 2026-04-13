#pragma once
#include "HelpFunction.h"
#include "Mouse.h"
#include "ColorEditor.h"
#include "Obj.h"


enum class ButtonStates { BTN_IDLE = 0, BTN_HOVER, BTN_PRESS, BTN_ACTIVE};

namespace gui {

	//Button class
	class Button : public Obj
	{
	protected:
		//classese declaration
		class EditorColorBK;
		class EditorColorOL;

		//Variables
		short unsigned buttonState;
		short unsigned id;
		bool sizeChangingMode;
		float height;
		float width;
		bool stayPressed;

		sf::Shape* shape;
		sf::Texture* textur;
	

		//Colors
		EditorColorBK* backgroundColor;
		EditorColorOL* outLineColor;


	public:
		Button(float x, float y, float width, float height,
			sf::Color idleColor = sf::Color::White,
			sf::Color hoverColor = sf::Color::White,
			sf::Color activeColor = sf::Color::White,
			sf::Color outLineIdleColor = sf::Color::Transparent,
			sf::Color OutLineHoverColor = sf::Color::Transparent,
			sf::Color OutLineActiveColor = sf::Color::Transparent);

		Button(const Button& other);
		virtual ~Button();

		//Accessors
		const bool isPressed() const;
		const short unsigned pressingState() const;
		virtual sf::Vector2f getPosition() const { return this->shape->getPosition();} 
		virtual sf::FloatRect getGlobalBounds() const { return this->shape->getGlobalBounds(); }
		short unsigned getId() const;
		sf::Vector2f getSize() const;
		bool isSizeChanging() const;
		bool isStayPressed() const;

		//Modifiers
		virtual void setPosition(const sf::Vector2f& pos);
		void setId(short unsigned id);
		virtual void setSize(float width, float hieght);
		void rotate(float deg);
		void setTextur(sf::Texture& textur);
		void setTexturRect(const sf::IntRect& rect);
		void setState(ButtonStates state);

		//Modifiers - Modes
		void setSizeChangingMode(bool);
		void setStayPressedMode(bool state);
	


		//Color - Function
		virtual void setColor(const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor,
			const sf::Color& outLineIdleColor = sf::Color::Transparent,
			const sf::Color& OutLineHoverColor = sf::Color::Transparent,
			const sf::Color& OutLineActiveColor = sf::Color::Transparent);

		void setBackgroundColor(const sf::Color& idleColor, int = 30);
		void setOutLine(const sf::Color& textIdleColor);
		void setOutlineThickness(float);


		//Functions
		virtual bool update(const sf::Vector2f& mousePos) override;
		virtual void render(sf::RenderTarget& target) override;
		virtual bool isMouseOver(const sf::Vector2f& mousePos) override;
		virtual void reset() override;


	protected:
		//Private functions
		virtual void updateColors();
		sf::Color lighten(const sf::Color&, int num);
		sf::Color darken(const sf::Color&, int num);
		virtual void setShapeSize(sf::Vector2f vec);




		//--------------------------------------------------------------
		// Editor color classes - declaration
		//		using ColorEditor template class
		//		Allow the user to change button colors in the editor.
		//		Works for background, and outline colors.
		//--------------------------------------------------------------


	public:
		class EditorColorBK : public ColorEditor <EditorColorBK>
		{
			using ColorEditor::ColorEditor;
		};

		class EditorColorOL : public ColorEditor <EditorColorOL>
		{
			using ColorEditor::ColorEditor;
		};

		gui::Button::EditorColorBK& BackgroundColor();
		gui::Button::EditorColorOL& OutLine();
	};
}

