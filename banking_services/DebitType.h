#pragma once
#include <string>

class DebitType 
{
public:
	int id;
	std::string name;
	double minSum;
	double duration;
	double interestRate;

	DebitType();

	DebitType(int _id, std::string _name, double _minSum, double _duration, double _interestRate);
};