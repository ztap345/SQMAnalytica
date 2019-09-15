#include "SQMDataRow.h"
#include <string>
#include <sstream>
#include <vector>

SQMDataRow::SQMDataRow(std::string data)
{
    std::stringstream stream(data);
    std::string temp;
    int counter(0);
	//split the raw data string by comma and populate the row
    while(std::getline(stream,temp,',')){

        if(counter == 0) //first is the date
            dt.setDate(temp);
        else if(counter == 1) //second is the time
            dt.setTime(temp);
        else //the rest is the data
            numericalData.push_back(std::stof(temp));

        counter++;
    }
}

std::string SQMDataRow::getRow(){
    std::vector<float> data = numericalData;
    std::stringstream stream;

    stream << dt.getDateTime() << ",";

    for(int i(0); i < data.size(); i++){
        stream << data[i];
        if(i < data.size()-1)
            stream << ",";
        else
            stream << std::endl;
    }

    return stream.str();
}

std::vector<float> SQMDataRow::getData(){
    return numericalData;
}

float SQMDataRow::getData(int index)
{
	return numericalData[index];
}

void SQMDataRow::eraseData() {
	numericalData.erase(numericalData.begin() + 1, numericalData.begin() + 6);
	numericalData.erase(numericalData.begin() + 2, numericalData.begin() + 4);
}

void SQMDataRow::AddElpsTim(float t)
{
	numericalData.push_back(t);
}

bool SQMDataRow::operator<(SQMDataRow & _row)
{
	return dt < _row.dt;
}
