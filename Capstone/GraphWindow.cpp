#include "GraphWindow.h"
/*

Credit:
	used Muzkaw's graph program for a base
	link to source: https://www.youtube.com/watch?v=BigJeW-hZaE
*/


GraphWindow::GraphWindow(RenderWindow * _win)
{
	win = _win;
	Initialize();
}

void GraphWindow::Initialize(float xmax, float ymax, float _tickSize, int _gridDetail, Color _lineColor) {
	size = (Vector2f)win->getSize();
	zero_position = Vector2f(size.x / 2, size.y / 2);
	ranges = Vector2f(xmax * 2, ymax * 2);
	tickSpacing = Vector2f(1, 1);
	tickSize = _tickSize;
	gridDetail = _gridDetail;
	xPixRange = size.x;
	yPixRange = size.y;
}

void GraphWindow::update() {
	win->clear(Color::White);
	drawGrid();
	drawAxis();
	drawTicks();
	win->display();
}

void GraphWindow::drawAxis() {
	Line xAxis(Vector2f(0,zero_position.y),Vector2f(size.x,zero_position.y),Color::Black);
	Line yAxis(Vector2f(zero_position.x, 0), Vector2f(zero_position.x, size.y), Color::Black);

	win->draw(xAxis);
	win->draw(yAxis);
}

void GraphWindow::drawTicks() {
	float numXTicks = ranges.x / tickSpacing.x, numYTicks = ranges.y / tickSpacing.y;
	std::vector<Line> xTicks, yTicks;

	for (int i = 0; i < numXTicks; i++) {
		Vector2f startTick = Vector2f(rest(zero_position.x, size.x / numXTicks) + i*size.x/numXTicks, zero_position.y - tickSize);
		Vector2f endTick = startTick + Vector2f(0,2*tickSize);
		xTicks.push_back(Line(startTick, endTick, Color::Black));
	}

	for (int i = 0; i < numYTicks; i++) {
		Vector2f startTick = Vector2f(zero_position.x - tickSize,rest(zero_position.y, size.y / numYTicks) + i * size.y / numYTicks);
		Vector2f endTick = startTick + Vector2f(2 * tickSize,0);
		yTicks.push_back(Line(startTick, endTick, Color::Black));
	}

	for (Line &l : xTicks) {
		win->draw(l);
	}
	for (Line &l : yTicks) {
		win->draw(l);
	}
}

void GraphWindow::drawGrid() {
	
	
	float numXGrid = (float)gridDetail * (ranges.x / tickSpacing.x), numYGrid = (float)gridDetail * (ranges.y / tickSpacing.y);
	std::vector<Line> xGrid, yGrid;

	for (int i = 0; i <= numXGrid +1; i++) {
		Vector2f startTick = Vector2f(rest(zero_position.x, (float)gridDetail * size.x /numXGrid) + (i - gridDetail) * size.x / numXGrid, 0);
		Vector2f endTick = startTick + Vector2f(0, size.y);
		xGrid.push_back(Line(startTick, endTick, gridColor));
	}

	for (int i = 0; i <= numYGrid +1; i++) {
		Vector2f startTick = Vector2f(0, rest(zero_position.y, (float)gridDetail * size.y / numYGrid) + (i - gridDetail) * size.y / numYGrid);
		Vector2f endTick = startTick + Vector2f(size.x, 0);
		yGrid.push_back(Line(startTick, endTick, gridColor));
	}

	for (Line &l : xGrid) {
		win->draw(l);
	}
	for (Line &l : yGrid) {
		win->draw(l);
	}
}

void GraphWindow::close()
{
	win->close();
}

bool GraphWindow::isOpen()
{
	return win->isOpen();
}

bool GraphWindow::pollEvent(Event * e)
{
	return win->pollEvent(*e);
}

/*
graphToScreen and screenToGraph scale coordinates back and forth
The origin of the window starts in the top left hand corner not in the center like most graphs do
The graph coordinate i.e. (1,1) would correspond to a point on a graph but in a window it would correspond to pixel (1,1)
The spacing between points (1,1) and (2,2) would look completely different between graph space and pixel space 
because of the difference of scale. ex. window can be 200x200 pixels but the graph would only be 10X10

therefore we must scale the points on the desired graph to the points on the window and vise-versa

graphToScreen:
	screen(x,y) = (graph(x,y) * winddowSize(x,y)) / graphRange(x,y) + origin(x,y)

screenToGraph:
	graph(x,y) = (screen(x,y) - origin(x,y)) * graphRange(x,y) / windowSize(x,y)
	

*/
Vector2f GraphWindow::graphToScreen(Vector2f graphCoords) {
	return Vector2f(xPixRange / ranges.x * (graphCoords.x - minimums.x) + zero_position.x,
					(yPixRange / ranges.y *-(graphCoords.y - minimums.y) + zero_position.y));
	//return Vector2f((graphCoords.x) * (size.x) / ranges.x + zero_position.x,
					//graphCoords.y * size.y / ranges.y + zero_position.y);
}

Vector2f GraphWindow::screenToGraph(Vector2f screenCoords) {
	return Vector2f((screenCoords.x-zero_position.x) / size.x * ranges.x,
					(screenCoords.y-zero_position.y) / size.y * ranges.y);
}

