/*
data structure to organize the input data from the SQM
stores the entire collection of data
*/

#ifndef SQMDATA_H
#define SQMDATA_H

#include <vector>
#include <string>
#include <fstream>
#include "SQMDataRow.h"
#include "SQMDay.h"
#include <iostream>
#include <sstream>


class SQMData
{
    public:
        SQMData(std::vector<std::ifstream*>, bool sort = true);//input a collection of data files
        void SQMAddData(std::vector<std::vector<std::string> > rawData);//stores the data in headers and rows
        void OutputData(std::string outFile = "SQMData.txt");//outputs the data to a csv file
		SQMDay getDayByIndex(int i); //return the day using the index
		int getNumDays(); //return the number of days stored

    private:
		void TrimData(std::vector<SQMDataRow> &rows);//trims the unwanted data
		float GetAverageTimeDiff(std::vector<SQMDataRow> rows);// returns average time between data measures
		std::string FormatData(std::string s);//formats the input data by removing all separating characters from the input files replacing them with commas to make parsing uniform
		void LoadDays(std::vector<SQMDataRow> rows);//find the data groups and store them into days
		std::vector<SQMDataRow> merge(std::vector<SQMDataRow> left, std::vector<SQMDataRow> right);//merge sort utility
		std::vector<SQMDataRow> mergeSort(std::vector<SQMDataRow> m);//merge sort
        std::vector<std::string> headers;//stores header info
		std::vector<SQMDay> days;//a list of grouped data rows to create a day of data
		bool doSort;
};

#endif // SQMDATA_H
