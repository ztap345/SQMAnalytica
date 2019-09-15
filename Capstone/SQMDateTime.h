/*
Class that stores Date and Time info 
provides comparison logic overides and formatting
*/
#ifndef SQMDATETIME_H
#define SQMDATETIME_H

#include <string>

class SQMDateTime
{
    public:
        SQMDateTime();//defualt constructoe
        SQMDateTime(std::string date, std::string time);//constructor to load the date and time automatically
        void setDate(std::string date);//set the date
        void setTime(std::string time);//set the time
        std::string getTime();//return a formatted time
        std::string getDate();//return a formatted date
        std::string getDateTime();//return a formatted date and time
		float getElspTime(SQMDateTime dt);
		bool isDifferentDay(SQMDateTime& dt);//Returns whether a passed date time day is different tham the current one
		bool operator<(SQMDateTime& dt);//override for the < operator
		bool operator>(SQMDateTime& dt);//override for the > operator
		bool operator<=(SQMDateTime& dt);//override for the <= operator
		bool operator>=(SQMDateTime& dt);//override for the >= operator
		float operator-(const SQMDateTime& dt);//override for the - operator
		float combinedDate = 0;//stores the date in terms of years
		float combinedTime = 0;//stored the time in terms of hours

    private:
		int sec;
        int min;
        int hour;
        int day;
        int month;
        int year;
};

#endif // SQMDATETIME_H
