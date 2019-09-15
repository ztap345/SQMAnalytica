#include "Utilities.h"
#include <cmath>
using namespace sf;
//used in original implementation of 
float rest(float x, float y) {
	return x - floor(x / y)*y;
}
//used to draw a circle inside a window when the window is passed to the function
void drawPoint(Vector2f p, float radius, RenderWindow & window, Color color)
{
	CircleShape c(radius);
	c.setFillColor(color);
	c.setPosition(p);
	c.setOrigin(radius, radius);
	window.draw(c);
}
//test function to draw different curves in curve window
double f(double x, int i) {
	if (i == 0)
		return 1 / (1+exp(-x));
	if (i == 1)
		return sqrt(x*x);
	if (i == 2)
		return x * x*x - x * x - x;
}
//line class. Uses VertexArray to draw lines faster with only 2 points and a color
Line::Line(Vector2f start, Vector2f end, Color _lineColor)
{
	line = VertexArray(Lines, 2);
	setLine(start,end);
	this->setColor(_lineColor);
}

void Line::setColor(Color _color)
{
	lineColor = _color;
	line[0].color = lineColor;
	line[1].color = lineColor;
}

void Line::setLine(Vector2f start, Vector2f end)
{
	line[0] = Vertex(start, lineColor);
	line[1] = Vertex(end, lineColor);
}

void Line::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(line, states);
}
