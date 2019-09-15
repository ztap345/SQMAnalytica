/*
this is a test class to draw a curve on a graph window
*/
#pragma once
#include "GraphWindow.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class CurveGraph :public GraphWindow
{
public:
	CurveGraph(RenderWindow*);
	void CurveInitialize(float xmax = 10, float ymax = 10, float _tickSize = 5, int _gridDetail = 2, int _curveDetail = 100, Color _lineColor = Color::Black);
	void update();
	void drawCurve();
	void buildCurve();
	void clearCurves();

private:
	Color lineColor;//color of any plotted line

	int curveDetail;//resolution of the curve. factored by 100
	int points;//number of points to detail in the curve
	int numCurves;//number of curves to be plotted

	std::vector<float> curvePoints;//list of x values that curve will be evaluated at
	std::vector<VertexArray> curves;//list of curves to be drawn
	std::vector<Color> lineColors = { Color::Red, Color::Green, Color::Blue };//color of each different line
};

