#pragma once
/*
Class used to store analytics of the desired value e.g. MPSAS or Temp

the index passed to the constructor is the index of the desired set of data
values in the rows of data
*/
#include<vector>
#include "SQMDataRow.h"

class SQMAnalytics
{
public:
	SQMAnalytics(std::vector<SQMDataRow> rows,int index); //initialize the class
	std::vector<float> GetAnalytics(); //returns a vector of the analytics in order  {min, max, avg, med, range}
	std::vector<SQMDataRow> GetRowsMinMax(); //returns the rows with the min and max value in them
	std::vector<float> getLoadedData(); //returns the data used to determine the analytics
	float getRange(); //return the range value of the desired data value

	float min, max, avg, med, range,size; //store the analytics and size
	std::string title; //store title of the data value e.g. "MPSAS" **NOT IMPLEMENTED""

private:
	void LoadAnalytics(std::vector<SQMDataRow> rows, int index); //loads the analytics
	void GetMedian(std::vector<SQMDataRow> rows, int index); //calculates the median
	std::vector<SQMDataRow> rowsMinMax; //stores the min and max rows
	std::vector<float> data; //stores the data points
};