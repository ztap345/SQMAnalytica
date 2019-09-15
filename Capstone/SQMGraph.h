#pragma once

/*
Main class that provides graph and window logic
*/
#include "GraphWindow.h"
#include "SQMData.h"
#include "Utilities.h"
#include <iostream>
#include <string>


class SQMGraph :
	public GraphWindow
{
public:
	SQMGraph(SQMData*);
	void Initialize(); // initialize the graph
	void update(Event e); // update function to handle events and changes
	void nextDay(); // function to increment the day
	void prevDay(); // function to decrement the day


private:
	void drawLabels();
	void drawAxis();
	void drawTicksAndGrid();
	void drawCurve();
	void LoadDay(); // load the Day that is being viewed
	void LoadInfo(RenderWindow * win);

	
	int currDayIndex;
	float maxTime;
	std::string titleText;
	SQMData* dataPointer;
	SQMDay currentDay;
	Text xText,yText,Title,dayCounter;
	Font labelFont;
	Color textColor = Color::Black;
	SimpleButton leftButton, rightButton, infoButton;
};

