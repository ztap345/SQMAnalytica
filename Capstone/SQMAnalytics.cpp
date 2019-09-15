#include "SQMAnalytics.h"


SQMAnalytics::SQMAnalytics(std::vector<SQMDataRow> rows, int index) {
	LoadAnalytics(rows, index);
}

std::vector<float> SQMAnalytics::GetAnalytics()
{
	return std::vector<float> {min, max, avg, med, range};
}

std::vector<SQMDataRow> SQMAnalytics::GetRowsMinMax()
{
	return rowsMinMax;
}

std::vector<float> SQMAnalytics::getLoadedData()
{
	return data;
}

float SQMAnalytics::getRange()
{
	return range;
}

void SQMAnalytics::LoadAnalytics(std::vector<SQMDataRow> rows, int index) {

	size = rows.size();

	int iMin(0), iMax(0);
	float loadData = rows[0].getData(index);

	min = loadData;
	max = loadData;
	avg += loadData;
	data.push_back(loadData);
	for (int i = 1; i < size; i++) {
		loadData = rows[i].getData(index);
		if (loadData < min) {
			min = loadData;
			iMin = i;
		}

		if (loadData > max) {
			max = loadData;
			iMax = i;
		}

		avg += loadData;
		data.push_back(loadData);
	}

	avg /= (float)size;
	GetMedian(rows, index);

	rowsMinMax.push_back(rows[iMin]);
	rowsMinMax.push_back(rows[iMax]);
	range = max - min;
}

void SQMAnalytics::GetMedian(std::vector<SQMDataRow> rows, int index) {
	int size = rows.size();
	if (size % 2 == 0) {
		med = rows[size/2].getData(index);
	}
	else {
		float medHi, medLo;
		medLo = rows[size/2].getData(index);
		medHi = rows[size / 2 + 1].getData(index);
		med = (medHi + medLo) / 2.0;
	}
}
