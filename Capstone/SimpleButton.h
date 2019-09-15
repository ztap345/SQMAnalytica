/*
this class is adapted from 
	https://pushbuttonreceivecode.com/blog/how-to-create-simple-buttons-for-your-sfml-game

this class creates a button that activates an event 
when the mouse in clicked or hovered inside it
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace sf;

namespace buttonState {
	enum {
		normal = 0,
		hovered = 1,
		clicked = 2,
		released = 3
	};
};

class SimpleButton : public Drawable
{
public:
	SimpleButton();
	SimpleButton(std::string _text, Font& _font, Vector2f position);

	void setFont(Font& _font);
	void setText(std::string _s);
	void setSize(int _size);
	void setPosition(Vector2f _position);
	FloatRect getGlobalBounds();
	FloatRect getLocalBound();
	void update(Event& e,RenderWindow& window);
	int getState();

private:
	virtual void draw(RenderTarget& target, RenderStates states) const;

	bool checkMouse(Vector2i mousePos);

	Color background;
	Color backgroundHover;
	Color backgroundClicked;
	Color textColor;
	Color textHover;
	Color textClicked;
	Color border;

	float borderthickness;
	Vector2f size;
	Vector2f position;
	int bttnState;

	RectangleShape button;
	Font font;
	int fontSize;
	Text text;
	Text textShadow;
	Clock internalClock;
};

