#pragma once
/*
GraphWindow class that handles the basic parameters and logic for graphing
*/
#include <SFML/Graphics.hpp>
#include <vector>
#include "Utilities.h"

using namespace sf;

class GraphWindow
{
public:
	GraphWindow() {};
	GraphWindow(RenderWindow *win);
	void Initialize(float xmax = 10, float ymax = 10, float _tickSize = 5, int _gridDetail = 2, Color _lineColor = Color::Black); //initialize the base graph parameters
	void update(); //class to draw in the win RenderWindow 
	void drawAxis(); //draws the axis
	void drawTicks(); //draws the ticks
	void drawGrid(); //draws the gridlines
	void close(); //close the graph
	bool isOpen(); //used to tell if the graph is open or not
	bool pollEvent(Event*); //used to poll event such as mouse clicks


	Vector2f graphToScreen(Vector2f); //function that converts cartesian coords to pixel coords
	Vector2f screenToGraph(Vector2f); ////function that converts pixel coords to cartesian coords

protected:
	RenderWindow * win;//pointer to window where the graph will be displayed
	Vector2f size;//size of the window
	Vector2f zero_position;//point where the origin lies within the window, normally in the center
	Vector2f ranges = Vector2f(0,0);//range of the x and y values that will be displayed
	Vector2f minimums = Vector2f(0, 0);//define the min and max coords for x and y
	Vector2f tickSpacing;//amount of space between ticks

	float xPadding=0, yPadding=0, endXPad=0, endYPad=0;//padding parameters
	float xPixRange = 0, yPixRange= 0; //pixel range of the graph
	float tickSize;//size of the tick marks
	int gridDetail;//resolution of the grid
	Color gridColor = Color(220, 220, 220); //default gridline color


	
};

