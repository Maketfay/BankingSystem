#pragma once
#include "DateTime.h"
#include <string>
#include <iostream>
#include <ctime>

DateTime DateTimeParse(std::string _dateTime)
{
	int firstpoint = 0;
	int secondpoint = 0;
	int therdpoint = 0;
	int fourthpoint = 0;
	int fivethpoint = 0;
	std::string day;
	std::string month;
	std::string year;
	std::string hour;
	std::string minute;
	std::string second;
	try {
		for (int i = 0; i < _dateTime.size(); i++)
		{
			if (_dateTime[i] == '-')
			{
				firstpoint = i;
				break;
			}
			day += _dateTime[i];
		}
		for (int i = firstpoint + 1; i < _dateTime.size(); i++)
		{
			if (_dateTime[i] == '-')
			{
				secondpoint = i;
				break;
			}
			month += _dateTime[i];
		}
		for (int i = secondpoint + 1; i < _dateTime.size(); i++)
		{
			if (_dateTime[i] == '.')
			{
				therdpoint = i;
				break;
			}
			year += _dateTime[i];
		}
		for (int i = therdpoint + 1; i < _dateTime.size(); i++)
		{
			if (_dateTime[i] == ':')
			{
				fourthpoint = i;
				break;
			}
			hour += _dateTime[i];
		}
		for (int i = fourthpoint + 1; i < _dateTime.size(); i++)
		{
			if (_dateTime[i] == ':')
			{
				fivethpoint = i;
				break;
			}
			minute += _dateTime[i];
		}
		for (int i = fivethpoint + 1; i < _dateTime.size(); i++)
		{
			second += _dateTime[i];
		}
		DateTime dateTime(std::stoi(day), std::stoi(month), std::stoi(year), std::stoi(hour), std::stoi(minute), std::stoi(second));
		return dateTime;
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

time_t ReturnInTime_t(DateTime& dateTime)
{
	struct tm tm;

	tm.tm_mday = dateTime.day;
	tm.tm_mon = dateTime.month - 1;
	tm.tm_year = dateTime.year - 1900;

	tm.tm_hour = dateTime.hour;
	tm.tm_min = dateTime.minute;
	tm.tm_sec = dateTime.second;

	time_t dt = mktime(&tm);

	return dt;
}

std::string DateTimeToString(DateTime& dateTime)
{
	int day = dateTime.day;
	int month = dateTime.month;
	int year = dateTime.year;
	int hour = dateTime.hour;
	int minute = dateTime.minute;
	int second = dateTime.second;
	std::string str = std::to_string(day) + '-' + std::to_string(month) + '-' + std::to_string(year)+'.'+ std::to_string(hour)+':'+ std::to_string(minute)+':'+ std::to_string(second);
	return str;
}

DateTime& DateTimeNow()
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	localtime_s(&tstruct, &now);
	DateTime d(tstruct.tm_mday, tstruct.tm_mon + 1, tstruct.tm_year + 1900, tstruct.tm_hour, tstruct.tm_min, tstruct.tm_sec);
	return d;
}

int DateTimeConfirm(DateTime dateTimeCredit) //0 - don't need in payment 1 - need payment
{
	DateTime now = DateTimeNow();
	int inow = now.year * 365 + now.month * 30 + now.day;
	int reservation = dateTimeCredit.year * 365 + dateTimeCredit.month * 30 + dateTimeCredit.day;
	int rez = inow - reservation;
	int difference = (now.hour * 60 * 60 + now.minute * 60 + now.second) + (rez * 24 * 60 * 60 - (dateTimeCredit.hour * 60 * 60 + dateTimeCredit.minute * 60 + dateTimeCredit.second));
	int goodDelay = 30*24*60*60;
	if (difference <= goodDelay) { return 0; }
	return 1;
}

int DateTimeCompare(DateTime first, DateTime second)//1 - equal , 0 - 1>2, 2 - 1<2
{
	time_t fr = ReturnInTime_t(first);
	time_t sc = ReturnInTime_t(second);

	time_t res = fr - sc;

	if (res == 0) return 1;
	if (res > 0) return 0;
	if (res < 0) return 2;
}

int DateTimeCompareDebit(DateTime first, DateTime second, int duration)//1 - equal , 0 - 1>2, 2 - 1<2
{
	int year = (int)duration / 12;
	int month = duration - year * 12;
	int day = ((duration - year * 12) - month) * 30;
	DateTime nwDt(day, month+1, year+1970, 0, 0, 0);
	time_t fr = ReturnInTime_t(first);
	time_t sc = ReturnInTime_t(second);
	time_t dr = ReturnInTime_t(nwDt);

	time_t res = fr - sc;

	if (res == dr) return 1;
	if (res > dr) return 0;
	if (res < dr) return 2;
}