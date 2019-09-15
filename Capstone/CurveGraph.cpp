#include "CurveGraph.h"
/*
Credit:
	used Muzkaw's graph program for a base
	link to source : https://www.youtube.com/watch?v=BigJeW-hZaE
*/

CurveGraph::CurveGraph(RenderWindow *_win)
{
	win = _win;
	CurveInitialize();
}

void CurveGraph::CurveInitialize(float xmax, float ymax, float _tickSize, int _gridDetail, int _curveDetail, Color _lineColor)
{
	Initialize(xmax,ymax,_tickSize,_gridDetail,_lineColor);
	curveDetail = _curveDetail;
	lineColor = _lineColor;
	numCurves = 3;

	points = curveDetail * 100;
	buildCurve();
}

void CurveGraph::update()
{
	win->clear(Color::White);
	drawGrid();
	drawAxis();
	drawTicks();
	drawCurve();
	win->display();
}

void CurveGraph::drawCurve()
{
	clearCurves();
	Color original = lineColor;
	for (int j = 0; j < curves.size(); j++) {

		for (int i = 0; i < points; i++) {
			curves[j].append(Vertex(graphToScreen(Vector2f(curvePoints[i], f(curvePoints[i], j))), lineColors[j]));
		}
		win->draw(curves[j]);
	}
}

void CurveGraph::buildCurve()
{
	for (int i = 0; i < points; i++) {
		curvePoints.push_back(ranges.x * (((2 * i) / (float)points) - 1));
	}
	for (int j = 0; j < numCurves; j++) {
		curves.push_back(VertexArray());
		curves[j].setPrimitiveType(LineStrip);
	}
}

void CurveGraph::clearCurves()
{
	for (int i = 0; i < curves.size(); i++) {
		curves[i].clear();
	}
}
