#pragma once
/*
Class that holds the rows by day, the analytics for the day
and logic for controlling the day (retrieving and setting data)
*/
#include <vector>
#include <string>
#include "SQMDataRow.h"
#include "SQMAnalytics.h"

class SQMDay
{
public:
	SQMDay();//default constructor
	void add(SQMDataRow row);//adds a data row into the day
	std::vector<SQMDataRow> GetDataRows();//returns the data rows
	std::string GetDay();//returns a string of the day range of the data
	void CalculateElspTim();//calculates elapsed time
	std::string GetAnalytics(); //returns the analytics for the day
	SQMAnalytics getMpsasData(); //returns the MPSAS data
	SQMAnalytics getTempData(); //returns the Temp data

	float getElapsedTime(); //returns the total elapsed time for the day


private:
	void updateDay();//updates the day range as new data is passed to it
	void LoadAnalyitcs(); //load the analytics into the vector
	std::vector<SQMDataRow> rows;//stores the rows
	std::string day;//stores the day range
	std::vector<SQMAnalytics> analytics;
	float avgElpsTime, totalElpsTime;//time analytics
	
};