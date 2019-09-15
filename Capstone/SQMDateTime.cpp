#include "SQMDateTime.h"
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

SQMDateTime::SQMDateTime()
{
}

SQMDateTime::SQMDateTime(std::string date, std::string time){
    setDate(date);
    setTime(time);
}

void SQMDateTime::setDate(std::string date){
    std::vector<std::string> splitDate;
    std::string split;
    std::stringstream stream(date);
    while(std::getline(stream,split,'/')){
        splitDate.push_back(split);
    }

    if (splitDate[0].size()>2){
        year = std::stoi(splitDate[0]);
        month = std::stoi(splitDate[1]);
        day = std::stoi(splitDate[2]);
    }
    else{
        year = std::stoi(splitDate[2]);
        month = std::stoi(splitDate[0]);
        day = std::stoi(splitDate[1]);
    }

	combinedDate += (float)year;
	combinedDate += (float)month / 12.0;
	combinedDate += (float)day / 365.0;
}

void SQMDateTime::setTime(std::string time){
    std::vector<std::string> splitTime;
    std::string split;
    std::stringstream stream(time);
    while(std::getline(stream,split,':')){
        splitTime.push_back(split);
    }

    hour = std::stoi(splitTime[0]);
    min = std::stoi(splitTime[1]);
    sec = std::stoi(splitTime[2]);

	combinedTime += (float)hour;
	combinedTime += (float)min / 60;
	combinedTime += (float)sec / 3600;
}

std::string SQMDateTime::getTime(){
    std::stringstream ss;
    ss << hour << ':' << min << ':' << sec;
    return ss.str();
}

std::string SQMDateTime::getDate(){
    std::stringstream ss;
    ss << month << '/' << day << '/' << year;
    return ss.str();
}

std::string SQMDateTime::getDateTime(){
    std::stringstream ss;
    ss << getDate() << "," << getTime();
    return ss.str();
}

float SQMDateTime::getElspTime(SQMDateTime dt)
{
	float t;
	float dmin(abs(min - dt.min)), dsec(abs(sec - dt.min));
	if (min < dt.min)
		dmin = abs((min + 60) - dt.min);
	if (sec < dt.sec)
		dsec = abs((sec + 60) - dt.sec);
	t = dmin + (dsec / 60.0);
	return t;
}

bool SQMDateTime::isDifferentDay(SQMDateTime & dt)
{
	float yearsGreater, mthsGreater, daysGreater;
	yearsGreater = year - dt.year;
	mthsGreater = ((float)month + (float)yearsGreater * 12.0) - (float)dt.month;
	daysGreater = ((float)day + (float)mthsGreater * 30.0) - (float)dt.day;
	
	return daysGreater != 0;
}

bool SQMDateTime::operator<(SQMDateTime & dt)
{
	if (combinedDate < dt.combinedDate)
		return true;
	if (combinedDate == dt.combinedDate && combinedTime < dt.combinedTime)
		return true;

	return false;
}

bool SQMDateTime::operator>(SQMDateTime& dt)
{
	if (combinedDate > dt.combinedDate)
		return true;
	if (combinedDate == dt.combinedDate && combinedTime > dt.combinedTime)
		return true;

	return false;
}

bool SQMDateTime::operator<=(SQMDateTime& dt)
{
	if (combinedDate > dt.combinedDate)
		return false;
	if (combinedDate == dt.combinedDate && combinedTime > dt.combinedTime)
		return false;

	return true;
}

bool SQMDateTime::operator>=(SQMDateTime& dt)
{
	if (combinedDate < dt.combinedDate)
		return false;
	if (combinedDate == dt.combinedDate && combinedTime < dt.combinedTime)
		return false;

	return true;
}

float SQMDateTime::operator-(const SQMDateTime & dt)
{
	float yearsGreater,mthsGreater,daysGreater,hrsGreater,minGreater,secGreater,difference;
	yearsGreater = year - dt.year;
	mthsGreater = ((float)month + (float)yearsGreater * 12.0) - (float)dt.month;
	daysGreater = ((float)day + (float)mthsGreater * 30.0) - (float)dt.day;
	hrsGreater = ((float)hour + (float)daysGreater * 24.0) - (float)dt.hour;
	minGreater = ((float)min + (float)hrsGreater * 60.0) - (float)dt.min;
	if (minGreater >= 0) {
		secGreater = std::abs((float)sec/60.0 - (float)dt.sec/60.0);
	}
	else {
		secGreater = -((float)sec / 60.0 - (float)dt.sec / 60.0);
	}

	difference = (float)minGreater + (float)secGreater;

	return difference;
}
