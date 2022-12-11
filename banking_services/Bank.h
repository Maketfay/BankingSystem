#pragma once
#include "UsersRepository.h"
#include "WalletRepository.h"
#include "UsersInformationRepository.h"
#include "PaymentRepository.h"
#include "CreditRepository.h"
#include "DebitRepository.h"
#include "DebitTypeRepository.h"
#include "BankStatus.h"
#include "CreditPayment.h"
#include "Credit.h"
#include "Vector.h"
#include <string>

class Users;

class Bank
{
public:

	UsersRepository* usersRepository;

	WalletRepository* walletRepository;

	UsersInformationRepository* usersInformationRepository;

	PaymentRepository* paymentRepository;

	CreditRepository* creditRepository;

	BankStatus* bankStatus;

	DebitRepository* debitRepository;

	DebitTypeRepository* debitTypeRepository;

	Bank();

	int SignIn(std::string login, std::string name, std::string surname, std::string patronymic, std::string phoneNumber, std::string pasportNumber, std::string type, std::string password);

	void PrintUsers();

	int IsValidUser(std::string login, std::string pasportNumber);//1 - it's valid user, 0 - this user there is, 2 - invalid login

	int GetIn(std::string login, std::string password);

	double GetBalance(int _userId);

	Payment* CreatePayment(int _userId, double amount, BalanceOperationType balanceOperationType);

	void EditInformation(int _userId);

	void MakePayment(int _walletId, double _amount, BalanceOperationType _balanceOperationType);

	std::string GetWalletNumber(int _userId);

	void ShowInformation(int _userId);

	bool Transaction(int _userIdFrom, std::string _walletNumberTo, double _amount);

	void EditPassword(int _userId, std::string oldPassword, std::string newPassword);

	Vector<CreditPayment> CalculateCreditPayment(Debt::Credit& credit);

	double ActualCreditPayment(int _userId,int  _walletId);

	bool OpenCredit(double _sum, int _duration, int _userId, int type);
	
	void MonthlyPayment(int _userId);

	void CreditInformation(int _userId);

	double GetRate();

	std::vector<int> ShowDebitTypes(double _sum, int maxDuration);

	bool OpenDebit(int _userId, double _sum, int maxDuration);

	void ActualDebit(int _userId);

	void DebitInformation(int _userId);
};