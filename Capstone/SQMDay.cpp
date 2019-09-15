#include <vector>
#include <string>
#include <sstream>
#include<iostream>
#include "SQMDay.h"
#include "SQMDateTime.h"



SQMDay::SQMDay()
{
	day = "";
}

void SQMDay::add(SQMDataRow row)
{
	rows.push_back(row);
	if (rows.size() > 1)
		updateDay();
	else
		day = rows[0].dt.getDate();
}

std::vector<SQMDataRow> SQMDay::GetDataRows()
{
	return rows;
}

std::string SQMDay::GetDay()
{
	return day;
}

void SQMDay::CalculateElspTim()
{
	float elapsedTime(0);
	if (rows.size() > 0) {
		rows[0].AddElpsTim(elapsedTime);
		for (int i(1); i < rows.size(); i++) {
			elapsedTime += rows[i].dt.getElspTime(rows[i-1].dt);
			rows[i].AddElpsTim(elapsedTime);
		}
	}
	totalElpsTime = elapsedTime;
}

std::string SQMDay::GetAnalytics()
{
	LoadAnalyitcs();
	std::stringstream stream;

	for (int i = 0; i < analytics.size(); i++) {
		std::vector<float> analyticsI = analytics[i].GetAnalytics();
		for (int j = 0; j < analyticsI.size(); j++) {
			stream << analyticsI[j];
			if (i < analyticsI.size() - 1)
				stream << ",";
			else
				stream << std::endl;
		}
	}

	 return stream.str();
}

SQMAnalytics SQMDay::getMpsasData()
{
	analytics[0].title = "MPSAS";
	return analytics[0];
}

SQMAnalytics SQMDay::getTempData()
{
	analytics[1].title = "Temp (\260C)";
	return analytics[1];
}

float SQMDay::getElapsedTime()
{
	return totalElpsTime;
}


void SQMDay::updateDay()
{
	int i(rows.size() - 1), im1(rows.size() - 2);
	if (rows[i].dt.isDifferentDay(rows[im1].dt))
		day += " -- " + rows[i].dt.getDate();
	else if (rows.size() < 2)
		day += rows[0].dt.getDate();
}

void SQMDay::LoadAnalyitcs()
{
	if (rows.size() > 0) {
		//indicies 0 and 1 are the MPSAS and Temp data repectively
		for (int index = 0; index < 2; index++) {
			SQMAnalytics *temp = new SQMAnalytics(rows,index);
			analytics.push_back(*temp);
			delete(temp);
		}
	}
}
