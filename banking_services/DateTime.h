#pragma once

class DateTime
{
public:
	int day;
	int month;
	int year;
	int hour;
	int minute;
	int second;


	DateTime();

	DateTime(int _day, int _month, int _year, int hour, int _minute, int _second);
};
