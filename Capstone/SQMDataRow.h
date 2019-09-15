/*
data structure to help organize the SQM's data
organizes the data into rows
*/

#ifndef SQMDATAROW_H
#define SQMDATAROW_H

#include "SQMDateTime.h"
#include <vector>
#include <string>

class SQMDataRow
{
    public:
        SQMDataRow(std::string data);//contructor that takes a data string to be parsed
        std::string getRow();//returns the row as a string
        std::vector<float> getData();//returns only the data
		float getData(int index);
		void eraseData();//erases data inside the row
		void AddElpsTim(float t);
		SQMDateTime dt;//stores date time info for the data
		bool operator<(SQMDataRow& _row); //opereator overload to see if a row comes before another
		
		
    private:
		std::vector<float> numericalData;//stores numerical data for use
};

#endif // SQMDATAROW_H
