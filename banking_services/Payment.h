#pragma once
#include <string>
#include "DateTime.h"
#include "BalanceOperationType.h"

class Payment
{
public:
	int id;
	int walletId;
	double amount;
	BalanceOperationType balanceOperationType;
	std::string dateTime;

	Payment();

	Payment(int _id, int _walletId, double _amount, BalanceOperationType _balanceOperationType, std::string _dateTime);
};
