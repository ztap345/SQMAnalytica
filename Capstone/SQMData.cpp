#include "SQMData.h"
#include "SQMDataRow.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

SQMData::SQMData(std::vector<std::ifstream*> inputDataCollection, bool sort)
{
	doSort = sort;//sets the selector for the sorting
	std::vector<std::vector<std::string> > data;//vector of data vectors

	//iterate through the file streams to format and store the data
	for (int i(0); i < inputDataCollection.size(); i++) {
		std::string temp;
		std::vector<std::string> readData;
		while (std::getline(*inputDataCollection[i], temp)) {
			readData.push_back(FormatData(temp));
		}
		data.push_back(readData);
	}

	//close the files
	for (int i(0); i < inputDataCollection.size(); i++) {
		inputDataCollection[i]->close();
	}

	//add the data to the central source
	SQMAddData(data);
}

void SQMData::SQMAddData(std::vector<std::vector<std::string> > rawData){

    std::string split;
    std::stringstream ss(rawData[0][1]);

	//load headers
    while(std::getline(ss,split,',')){
        headers.push_back(split);
    }

	std::vector<SQMDataRow> rows;

	//load rows
    for(int i(0); i<rawData.size(); i++){
        for(int j(2); j<rawData[i].size(); j++){
            std::string temp = rawData[i][j];
            SQMDataRow row(temp);
            rows.push_back(row);
        }
    }

	if (doSort) {
		std::cout << "Sorting..." << std::endl;
		std::sort(rows.begin(), rows.end());
		//rows = mergeSort(rows);
		std::cout << "Finished!" << std::endl;
	}

	TrimData(rows);

	LoadDays(rows);

}

//iterate through the days and output to a text file row by row in csv format
void SQMData::OutputData(std::string outFile){
    std::ofstream output(outFile);
	std::string miscHeaders[] = { "min MPSAS", "max MPSAS", "avg MPSAS","medn MPSAS", "min Temp", "max Temp", "avg Temp", "medn Temp" };

	//write headers to file
    for(int i(0); i < headers.size(); i++){
        if(i < headers.size()-1)
            output << headers[i] << ",";
        else
            output << headers[i] << std::endl;
    }
	//write the data from each day to the file
	for (int i(0); i < days.size(); i++) {
		std::vector<SQMDataRow> temp = days[i].GetDataRows();
		output << days[i].GetDay() << std::endl;
		for (int j(0); j < temp.size(); j++) {
			output << temp[j].getRow();
		}

		for (int j(0); j < 6; j++) {
			output << miscHeaders[j];
			if (j < 5)
				output << ",";
			else
				output << std::endl;
		}
		//write the analytics to the file at the end of each day
		output << days[i].GetAnalytics();
		output << std::endl << std::endl;
	}
   
    output.close();
}
//return the day by index
SQMDay SQMData::getDayByIndex(int i)
{
	if (i >= 0 && i < days.size()) {
		return days[i];
	}
	if (i<0) {
		std::cout << "index out of range!" << std::endl;
		return SQMDay();
	}
	std::cout << "There are no more days available" << std::endl;
	return SQMDay();;
}
//return the number of days
int SQMData::getNumDays()
{
	return days.size();
}
//Trim the unneccesary data and headers from each row and add the elapsed time header
void SQMData::TrimData(std::vector<SQMDataRow> &rows) {

	headers.erase(headers.begin()+3,headers.begin()+8);
	headers.erase(headers.begin() + 4, headers.begin() + 6);

	for (int j(0); j < rows.size(); j++) {
		rows[j].eraseData();
	}

	headers.push_back("Elapsed Time(min)");
}
//loads each rows data into a SQMDay class, populating the vector for the days
void SQMData::LoadDays(std::vector<SQMDataRow>  rows) {
	float avgDiff = GetAverageTimeDiff(rows); //used as a threshold to determine where a day ends and another begnins
	int i = 0;

	while (i < rows.size()) {
		//create a new day pointer
		SQMDay *temp = new SQMDay();
		//iterate through the rows
		while ((i+1) < rows.size()) {
			//push the rows into the day pointer unless the delta between days is less than threshold
			if ((rows[i + 1].dt - rows[i].dt) < avgDiff) {
				temp->add(rows[i]);
				i++;
				
			}
			else {
				i++;
				break; //if threshold is breached, break the loop
			}
		}
		i++;
		//dereference the pointer and add it to the day vector unless the day is empty
		if(temp->GetDataRows().size() > 0)
			days.push_back(*temp);
		delete(temp); //delete the pointer to clear the previous days data to prepare for loading the next day
	}

	//calculates the elapsed time for each day created
	for (int i(0); i < days.size(); i++) {
		days[i].CalculateElspTim();
	}
}

//calculate the average time difference in the data
float SQMData::GetAverageTimeDiff(std::vector<SQMDataRow> rows) {
	float avg(0);
	
	for (int i = 0; i < rows.size()-1; i++) {
		float diff = rows[i + 1].dt - rows[i].dt;
		avg += diff;
	}

	avg /= (float)rows.size();
	return avg;
}

std::string SQMData::FormatData(std::string s)
{
	//remove trouble newline characters and replace /t with spaces to preserve data
	s.erase(remove(s.begin(), s.end(), '\n'), s.end());
	std::replace(s.begin(), s.end(), '\t', ' ');

	//iterate through string and erase duplicate spaces that are adjacent
	for (int i(s.length() - 1); i > 0; i--) {
		if (s[i] == ' ' && s[i - 1] == ' ')
			s.erase(i, 1);
	}

	//Erase last space if at the end of the string
	if (s[s.length() - 1] == ' ') {
		s.erase(s.length() - 1, 1);
	}

	//convert to CSV
	replace(s.begin(), s.end(), ' ', ',');
	return s;
}

/*merge sort implementations*/
std::vector<SQMDataRow> SQMData::merge(std::vector<SQMDataRow> left, std::vector<SQMDataRow> right)
{
	std::vector<SQMDataRow> result;
	while (left.size() > 0 || right.size() > 0) {
		if (left.size() > 0 && right.size() > 0) {
			if (left.front().dt <= right.front().dt) {
				result.push_back(left.front());
				left.erase(left.begin());
			}
			else {
				result.push_back(right.front());
				right.erase(right.begin());
			}
		}
		else if (left.size() > 0) {
			for (int i(0); i < left.size(); i++)
				result.push_back(left[i]);
			break;
		}
		else if (right.size() > 0) {
			for (int i(0); i < right.size(); i++)
				result.push_back(right[i]);
			break;
		}
	}

	return result;
}

std::vector<SQMDataRow> SQMData::mergeSort(std::vector<SQMDataRow> m)
{
	if (m.size() <= 1)
		return m;

	std::vector<SQMDataRow> left, right, result;
	int middle = (m.size() + 1) / 2;

	for (int i(0); i < m.size(); i++) {
		if (i < middle)
			left.push_back(m[i]);
		else
			right.push_back(m[i]);
	}

	left = mergeSort(left);
	right = mergeSort(right);
	result = merge(left, right);

	return result;
}