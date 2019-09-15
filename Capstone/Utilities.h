#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "SimpleButton.h"

using namespace sf;
//function definitions
float rest(float, float);

void drawPoint(Vector2f p, float radius, RenderWindow &window, Color color);

double f(double x, int i);
//class to make drawing lines easier
class Line : public Drawable {
public:
	Line(Vector2f,Vector2f, Color _lineColor = Color::White); //initialize the line
	void setColor(Color); //set the line color later if desired
	void setLine(Vector2f, Vector2f); //set the line endpoints later if desired
private:
	virtual void draw(RenderTarget&, RenderStates)const; //used to draw the line in a window using window.draw(line)
	VertexArray line; //holds the line data
	Color lineColor; //holds the line color
};

