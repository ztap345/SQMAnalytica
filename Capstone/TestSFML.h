#pragma once
//test class made to showcase SFML's strengths
#include "GraphWindow.h"
#include <vector>

class movingCircle {
public:
	movingCircle(float x, float y);
	void reverseXVel();
	void reverseYvel();
	void updatePos();
	Vector2f getPos();
	CircleShape getCircle();
	float getRadius();

private:
	float xVel, yVel;
	CircleShape circle;
};

class TestSFML
{
public:
	
	TestSFML();
	~TestSFML();
private:
	void update();

	RenderWindow* win;
	std::vector<movingCircle> circles;
	float circleVel = 1;
};



