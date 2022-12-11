#pragma once
#include <string>
class BankStatus
{
private:

	double balance;

	double interestRate;

public:

	void UpdateDate();

	BankStatus();

	BankStatus(double balance, double interestRate);

	double GetBalance();
		
	double GetInterestRate();

	void AddToBankBalance(double amount);

	bool TakeCredit(double amount);

	void SubBalance(double amount);

};