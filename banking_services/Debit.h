#pragma once
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "DebitType.h"

namespace Debt
{
	class Debit
	{
	public:
		int id;
		std::string dateTime;
		bool isClosed;
		double sum;	
		int userId;
		int debitTypeId;
		
		Debit();

		Debit(std::string _dateTime, double _sum, int _userId, int _type);

		Debit(int _id, std::string _dateTime, bool _isClosed, double _sum, int _userId, int _type);

	};
}