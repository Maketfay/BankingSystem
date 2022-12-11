#pragma once
#include <iostream>
#include <string>
#include <fstream>

namespace Debt
{
	class Credit
	{
	public:
		int id;
		std::string dateTime;
		bool isClosed;
		double sum;
		int duration;
		int userId;
		double interestRate;
		int type;                 //0 - Annuity, 1 - differentiated

		Credit();

		Credit(std::string _dateTime, double _sum, int duration, int userId, double interestRate, int type);

		Credit(int _id, std::string _dateTime, bool _isClosed, double _sum, int duration, int userId, double interestRate, int type);

	};
}