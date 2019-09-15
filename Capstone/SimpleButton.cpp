#include "SimpleButton.h"

SimpleButton::SimpleButton(){
	internalClock = Clock();
}

SimpleButton::SimpleButton(std::string _text, Font & _font, Vector2f _position)
{
	internalClock = Clock();

	position = _position;

	bttnState = buttonState::normal;

	textColor = Color(255,255,255);
	textHover = textColor;
	textClicked = textColor;
	background = Color(120, 130, 145);
	backgroundHover = Color(0,0,0,145);
	backgroundClicked = Color(150,0,0);
	border = Color(255, 255, 255, 100);

	text.setString(_text);
	text.setFont(_font);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setFillColor(textColor);
	

	borderthickness = 1.0;
	size = Vector2f(text.getGlobalBounds().width * 1.5, text.getGlobalBounds().height * 1.5);

	button = RectangleShape(size);
	button.setOutlineThickness(borderthickness);
	button.setOrigin(button.getGlobalBounds().width / 2, button.getGlobalBounds().height / 2);
	button.setPosition(position);

	text.setPosition(Vector2f(button.getPosition().x,button.getPosition().y - button.getGlobalBounds().height / 4));

	textShadow.setFont(_font);
	textShadow = text;
	textShadow.setOrigin(textShadow.getGlobalBounds().width / 2, textShadow.getGlobalBounds().height / 2);
	textShadow.setPosition(text.getPosition().x + 3.0,text.getPosition().y+3.0);
}

void SimpleButton::setFont(Font & _font)
{
	text.setFont(_font);
	textShadow.setFont(_font);
}

void SimpleButton::setText(std::string _s)
{
	text.setString(_s);
	textShadow = text;
}

void SimpleButton::setSize(int _size)
{
	fontSize = _size;

	text.setCharacterSize(fontSize);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	
	textShadow.setCharacterSize(_size);
	textShadow.setOrigin(textShadow.getGlobalBounds().width / 2, textShadow.getGlobalBounds().height / 2);

	size = Vector2f(text.getGlobalBounds().width * 1.5, text.getGlobalBounds().height * 1.5);
	button = RectangleShape(size);
	button.setOutlineThickness(borderthickness);
}

void SimpleButton::setPosition(Vector2f _position)
{
	position = _position;
}

FloatRect SimpleButton::getGlobalBounds()
{
	return button.getGlobalBounds();
}

FloatRect SimpleButton::getLocalBound()
{
	return button.getLocalBounds();
}

void SimpleButton::update(Event & e, RenderWindow & window)
{
	size = Vector2f(text.getGlobalBounds().width * 1.5, text.getGlobalBounds().height * 1.75);
	
	button = RectangleShape(size);
	button.setOutlineThickness(borderthickness);
	button.setOrigin(button.getGlobalBounds().width / 2, button.getGlobalBounds().height / 2);
	button.setPosition(position);

	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setPosition(Vector2f(button.getPosition().x, button.getPosition().y - button.getGlobalBounds().height / 4));
	text.setFillColor(textColor);

	textShadow.setOrigin(textShadow.getGlobalBounds().width / 2, textShadow.getGlobalBounds().height / 2);
	textShadow.setPosition(text.getPosition().x + 3.0, text.getPosition().y + 3.0);
	textShadow.setFillColor(Color(0,0,0));

	bool mouseInButton = checkMouse(Mouse::getPosition(window));
	
	//uses a timer to prevent clicking too fast
	Time pressTimer = internalClock.getElapsedTime();

	bttnState = buttonState::normal;
	if (e.type == Event::MouseMoved) {
		if (mouseInButton)
			bttnState = buttonState::hovered;
		else
			bttnState = buttonState::normal;
	}
	else if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left) {
		if (pressTimer.asMilliseconds() > 250) {
			if (mouseInButton) {
				bttnState = buttonState::clicked;
				internalClock.restart();
			}
			else {
				bttnState = buttonState::normal;
			}
		}
	}
	else if (e.type == Event::MouseButtonReleased && e.mouseButton.button == Mouse::Left) {
		if (mouseInButton)
			bttnState = buttonState::hovered;
		else
			bttnState = buttonState::normal;
	}

	switch (bttnState) {
		case buttonState::normal:
			button.setFillColor(background);
			text.setFillColor(textColor);
			break;
		case buttonState::hovered:
			button.setFillColor(backgroundHover);
			text.setFillColor(textHover);
			break;
		case buttonState::clicked:
			button.setFillColor(backgroundClicked);
			text.setFillColor(textClicked);
			break;
		default:
			break;
	}
}

int SimpleButton::getState()
{
	return bttnState;
}

void SimpleButton::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(button, states);
	target.draw(textShadow,states);
	target.draw(text, states);
}

bool SimpleButton::checkMouse(Vector2i mousePos)
{
	return 
		(
		mousePos.x >= button.getPosition().x - button.getGlobalBounds().width/2 &&
		mousePos.x <= button.getPosition().x + button.getGlobalBounds().width/2 &&
		mousePos.y >= button.getPosition().y - button.getGlobalBounds().height/2 &&
		mousePos.y <= button.getPosition().y + button.getGlobalBounds().height/2 
		);
}
