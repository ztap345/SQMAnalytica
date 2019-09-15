#include "SQMGraph.h"



SQMGraph::SQMGraph(SQMData* _data)
{
	// graph setup
	win = new RenderWindow(VideoMode(800, 600), "SQM Analytica", Style::Default); // creates window for the graph
	win->setKeyRepeatEnabled(false);
	dataPointer = _data; // using pointer to prevent the data from copying and filling up memory
	if (!labelFont.loadFromFile("fonts\\calibri.ttf")) {
		std::cout << "Cannot find font file!\n";
	}
	Initialize();
}

void SQMGraph::Initialize()
{
	//multiplication factors used for padding of the axis/gridlines
	size = (Vector2f)win->getSize();
	xPadding = .075*size.x;
	yPadding = .1125*size.y;
	endXPad = .05*size.x;
	endYPad = .075*size.y;
	zero_position = Vector2f(xPadding, size.y - yPadding);
	xPixRange = size.x - endXPad - xPadding;
	yPixRange = size.y - endYPad - yPadding;
	tickSize = 20; //40 pixels top to bottom

	// starts the graph of SQM data
	currDayIndex = -1;
	nextDay();

	// create and initialize the buttons for the current graph
	leftButton = SimpleButton("Prev Day", labelFont, Vector2f(0, 0));
	rightButton = SimpleButton("Next Day", labelFont, Vector2f(0, 0));
	infoButton = SimpleButton("INFO", labelFont, Vector2f(0, 0));
	infoButton.setSize(20);

	leftButton.setPosition(Vector2f(leftButton.getLocalBound().width/2, size.y - leftButton.getLocalBound().height/2));
	rightButton.setPosition(Vector2f(size.x - rightButton.getLocalBound().width/2, size.y - rightButton.getLocalBound().height/2));
	infoButton.setPosition(Vector2f(infoButton.getLocalBound().width / 2, infoButton.getLocalBound().height));
}


void SQMGraph::update(Event e)
{
	// update all the elements of the graph
	// updates the buttons
	leftButton.update(e, *win);
	rightButton.update(e, *win);
	infoButton.update(e, *win);

	//button logic to choose which function to use depending on the button clicked
	if (leftButton.getState() == buttonState::clicked)
		prevDay();
	else if (rightButton.getState() == buttonState::clicked)
		nextDay();
	else if (infoButton.getState() == buttonState::clicked) {
		// open sub window to display current graph statistics
		RenderWindow InfoWindow (VideoMode(300, 600), "Day Info", Style::Default);
		win->setVisible(false);
		while (InfoWindow.isOpen()) {
			Event event;
			while (InfoWindow.pollEvent(event))
			{
				if (event.type == Event::Closed) {
					InfoWindow.close();
					win->setVisible(true);
				}
			}
			LoadInfo(&InfoWindow);
		}
	}

	// update and draw grid elements and buttons
	win->clear(Color::White);
	drawTicksAndGrid();
	drawAxis();
	drawLabels();
	drawCurve();
	win->draw(leftButton);
	win->draw(rightButton);
	win->draw(infoButton);
	win->display();
}


// logic for decrementing and incrementing days
void SQMGraph::nextDay()
{
	if (currDayIndex + 1 >= dataPointer->getNumDays()) {
		std::cout << "There are no more days, resetting to the last day..." << std::endl;
		currDayIndex = dataPointer->getNumDays() - 1;
	}
	else
		currDayIndex++;
	LoadDay();

}

void SQMGraph::prevDay()
{
	if (currDayIndex - 1 < 0) {
		std::cout << "There are no more previous days, resetting to the first day..." << std::endl;
		currDayIndex = 0;
	}
	else
		currDayIndex--;
	LoadDay();
}



void SQMGraph::drawLabels()
{
	float xCenter = (xPadding + (size.x - endXPad)) / 2,
		  yCenter = (endYPad + (size.y - yPadding)) / 2;
	//set x label text
	xText = Text("Elapsed Time (min)",labelFont,24);
	xText.setFillColor(textColor);
	xText.setPosition(xCenter - xText.getLocalBounds().width/2,size.y*.925);

	//set y label text
	yText = Text("Brightness (mpsas)",labelFont,24);
	yText.setFillColor(textColor);
	yText.setRotation(270.0);
	yText.setPosition(size.x*.006, yCenter + yText.getLocalBounds().width / 2);

	//set Title label text
	Title = Text(titleText,labelFont,32);
	Title.setFillColor(textColor);
	Title.setPosition(xCenter - Title.getLocalBounds().width / 2,0);

	//set counter label
	int numDays = dataPointer->getNumDays();
	std::stringstream ss;
	ss << currDayIndex + 1 << "\\" << numDays;
	dayCounter = Text(ss.str(), labelFont, 12);
	dayCounter.setFillColor(textColor);
	dayCounter.setPosition(size.x-dayCounter.getGlobalBounds().width-50,0);
	
	win->draw(Line(Vector2f(xPadding, endYPad), Vector2f(size.x - endXPad, endYPad), Color::Black));
	win->draw(Line(Vector2f(size.x-endXPad,endYPad),Vector2f(size.x - endXPad,size.y-yPadding), Color::Black));
	win->draw(xText);
	win->draw(yText);
	win->draw(Title);
	win->draw(dayCounter);
	
}

void SQMGraph::drawAxis()
{
	// draw 2 lines for the axis
	Vector2f endX(size.x-endXPad, size.y - yPadding), endY(xPadding,endYPad);
	Line xAxis(zero_position, endX,Color::Black);
	Line yAxis(zero_position, endY, Color::Black);
	win->draw(xAxis);
	win->draw(yAxis);
}

void SQMGraph::drawTicksAndGrid()
{
	// contains logic for drawing the number labels for the tick marks

	// draw tick lines for the x axis
	int xTickOffset(10),yTickOffset(1),labelCountOffset(5),numTicks(0);
	float currentX(0), currentY(0);

	while(currentX <= ranges.x + xTickOffset){
		Vector2f xTickCenter = graphToScreen(Vector2f(currentX,0));
		if (currentX >= ranges.x) {
			xTickCenter = graphToScreen(Vector2f(ranges.x, 0));
		}
		if (numTicks <= (int)ranges.x / xTickOffset) {
			win->draw(Line(xTickCenter, graphToScreen(Vector2f(currentX, ranges.y)), gridColor));
		}
		win->draw(Line(Vector2f(xTickCenter.x, xTickCenter.y - (tickSize / 2)), Vector2f(xTickCenter.x, xTickCenter.y + (tickSize / 2)), Color::Black));

		if (numTicks % labelCountOffset == 0 || numTicks == 0 || numTicks == ((int)ranges.x + xTickOffset) / xTickOffset) {
			Text numberLabel(std::to_string((int)currentX),labelFont,12);
			if (currentX >= ranges.x) {
				numberLabel.setString(std::to_string((int)ranges.x));
			}
			numberLabel.setFillColor(Color::Black);
			Vector2f labelPos = Vector2f(xTickCenter.x - numberLabel.getLocalBounds().width / 2, xTickCenter.y + tickSize / 2);
			numberLabel.setPosition(labelPos);
			win->draw(numberLabel);
		}
		numTicks++;
		currentX += xTickOffset;
	}

	numTicks = 0;
	// draw tick lines for the y axis
	while (currentY <= ranges.y + yTickOffset) {
		Vector2f yTickCenter = graphToScreen(Vector2f(0,currentY));
		if (currentY >= ranges.y) {
			yTickCenter = graphToScreen(Vector2f(0,ranges.y));
		}
		if (numTicks <= (int)ranges.y / yTickOffset) {
			win->draw(Line(yTickCenter, graphToScreen(Vector2f(ranges.x, currentY)), gridColor));
		}
		win->draw(Line(Vector2f(yTickCenter.x - (tickSize / 2), yTickCenter.y ), Vector2f(yTickCenter.x + (tickSize / 2), yTickCenter.y ), Color::Black));
		if (numTicks % labelCountOffset == 0 || numTicks == 0 || numTicks == (int)ranges.y / yTickOffset) {
			Text numberLabel(std::to_string((int)currentY), labelFont, 12);
			if (currentY >= ranges.y) {
				numberLabel.setString(std::to_string((int)ranges.y));
			}
			numberLabel.setFillColor(Color::Black);
			Vector2f labelPos = Vector2f(yTickCenter.x - tickSize / 2 - numberLabel.getLocalBounds().width, yTickCenter.y - numberLabel.getLocalBounds().height);
			numberLabel.setPosition(labelPos);
			win->draw(numberLabel);
		}
		numTicks++;
		currentY += yTickOffset;
	}
	
}

void SQMGraph::drawCurve()
{
	// create and draw curve on the graph using the current days data
	VertexArray curve;
	curve.setPrimitiveType(LineStrip);
	float t(0), size(currentDay.getMpsasData().size);
	for (float i(0); i < size; i++) {
		Vector2f point = graphToScreen(Vector2f(t, currentDay.getMpsasData().getLoadedData()[i]));
		Vertex temp = Vertex(point,Color::Blue);
		curve.append(temp);
		t += maxTime / size;
	}
	win->draw(curve);
}

void SQMGraph::LoadDay()
{
	// loads the data when the day is changed
	currentDay = dataPointer->getDayByIndex(currDayIndex);
	if (currentDay.GetDay() != "") {
		std::cout << "The day has been loaded." << std::endl;
		titleText = currentDay.GetDay();
		drawLabels();
		maxTime = currentDay.getElapsedTime();
		float mpsasMin = currentDay.getMpsasData().getLoadedData()[0];
		minimums = Vector2f(0, 0);//set hard minimums for the graph. first data value for MPSAS value and 0 for time
		ranges = Vector2f(maxTime, 25);//set ranges using maximum values. 25 is the largest MPSAS reasonable and t is the elapsed time
	}
	else {
		std::cout << "there was no title..." << std::endl;
	}
	
}

void SQMGraph::LoadInfo(RenderWindow * info)
{
	// loads the analyitcs for the day for ouput to the InfoWindow
	std::vector<std::string> headers = { "Min","Max","Avg","Med", "Range" };
	std::vector<SQMAnalytics> analytics;
	analytics.push_back(currentDay.getMpsasData());
	analytics.push_back(currentDay.getTempData());
	Text MPSAS, TEMP;
	float xPos();
	Vector2f lastHeight(0, 0);
	for (int i(0); i < analytics.size(); i++) {
		std::stringstream ss;
		ss << analytics[i].title << " Analytics:\n\t";
		for (int j(0); j < headers.size(); j++) {
			ss << headers[j] << ":\t" << analytics[i].GetAnalytics()[j] << "\n\t";
		}
		ss << "\n";

		if (i == 0) {
			MPSAS = Text(ss.str() , labelFont, 32);
			MPSAS.setFillColor(textColor);
			lastHeight.x = (info->getSize().x - MPSAS.getGlobalBounds().width) / 2;
			MPSAS.setPosition(lastHeight);
			lastHeight.y += MPSAS.getGlobalBounds().height;
		}
		else if (i == 1) {
			TEMP = Text(ss.str() , labelFont, 32);
			TEMP.setFillColor(textColor);
			lastHeight.x = (info->getSize().x - TEMP.getGlobalBounds().width) / 2;
			TEMP.setPosition(lastHeight);
			lastHeight.y += TEMP.getGlobalBounds().height;
		}
		
	}
	info->clear(Color::White);
	info->draw(MPSAS);
	info->draw(TEMP);
	info->display();
}
