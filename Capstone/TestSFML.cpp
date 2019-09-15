#include "TestSFML.h"
#include <cmath>
#include <ctime>

movingCircle::movingCircle(float x, float y)
{
	circle = CircleShape();
	circle.setFillColor(sf::Color::Blue);
	circle.setRadius(30);
	circle.setOrigin(30, 30);
	circle.setPosition(x, y);

	xVel = (float)rand() / (float)RAND_MAX *.1;
	yVel = (float)rand() / (float)RAND_MAX *.1;
}

void movingCircle::reverseXVel()
{
	xVel = -xVel;
}

void movingCircle::reverseYvel()
{
	yVel = -yVel;
}

void movingCircle::updatePos()
{
	Vector2f newPos(circle.getPosition().x + xVel, circle.getPosition().y + yVel);
	circle.setPosition(newPos);
}

Vector2f movingCircle::getPos()
{
	return circle.getPosition();
}

CircleShape movingCircle::getCircle()
{
	return circle;
}

float movingCircle::getRadius()
{
	return circle.getRadius();
}

TestSFML::TestSFML()
{
	win = new RenderWindow(VideoMode(800, 600), "Test SFML", Style::Default);
	srand(time(NULL));
	while (win->isOpen())
	{
		win->clear(sf::Color(105, 105, 105,255));
		sf::Event e;
		if (win->pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				win->close();
			}
			else if (e.type == sf::Event::MouseButtonPressed) {
				if (e.mouseButton.x <= 800 && e.mouseButton.y <= 600 && e.mouseButton.x >= 0 && e.mouseButton.y >= 0) {
					movingCircle c(e.mouseButton.x, e.mouseButton.y);
					circles.push_back(c);
				}
			}
		}
		for (int i = 0; i < circles.size(); i++) {
			circles[i].updatePos();
			if (circles[i].getPos().x - circles[i].getRadius() < 0 || circles[i].getPos().x + circles[i].getRadius() > 800) {
				circles[i].reverseXVel();
			}
			if (circles[i].getPos().y - circles[i].getRadius() < 0 || circles[i].getPos().y + circles[i].getRadius() > 600) {
				circles[i].reverseYvel();
			}
			win->draw(circles[i].getCircle());
		}
		win->display();
	}
}


TestSFML::~TestSFML()
{
}



