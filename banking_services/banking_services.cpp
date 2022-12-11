#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <conio.h>
#include <time.h>
#include <math.h>

#include "IsAutorised.h"
#include "IRepository.h"
#include "UsersRepository.h"
#include "Users.h"
#include "Bank.h"
#include "Wallet.h"
#include "Credit.h"
#include "WalletRepository.h"
#include "UsersInformation.h"
#include "UsersInformationRepository.h"
#include "GenerateAccountNumber.h"
#include "Hashing.h"
#include "ActualUser.h"
#include "Payment.h"
#include "PaymentRepository.h"
#include "CreditRepository.h"
#include "BankStatus.h"
#include "DateTime.h"
#include "DateTimeUtilit.h"
#include "FileException.h"
#include "Vector.h"
#include "DebitType.h"
#include "Debit.h"
#include "DebitTypeRepository.h"
#include "DebitRepository.h"

#define BankAccountNumber "0000000000"

using namespace std;
using json = nlohmann::json;

#pragma region Credit

Debt::Credit::Credit() 
{

}

Debt::Credit::Credit(string _dateTime, double _sum, int _duration, int _userId, double _interestRate, int _type)
{
	id = CreditRepository::GetInstance()->GetId();
	dateTime = _dateTime;
	sum = _sum;
	duration = _duration;
	userId = _userId;
	interestRate = _interestRate;
	isClosed = 0;
	type = _type;
}

Debt::Credit::Credit(int _id, string _dateTime,bool _isClosed, double _sum, int _duration, int _userId, double _interestRate, int _type)
{
	id = _id;
	dateTime = _dateTime;
	sum = _sum;
	duration = _duration;
	userId = _userId;
	interestRate = _interestRate;
	isClosed = _isClosed;
	type = _type;
}

#pragma endregion Credit

#pragma region DebitType

DebitType::DebitType() {}

DebitType::DebitType(int _id, string _name, double _minSum, double _duration, double _interestRate)
{
	id = _id;
	name = _name;
	minSum = _minSum;
	duration = _duration;
	interestRate = _interestRate;
}

#pragma endregion DebitType

#pragma region Debit

Debt::Debit::Debit() {}

Debt::Debit::Debit(string _dateTime, double _sum, int _userId, int _type)
{
	id = DebitRepository::GetInstance()->GetId();
	dateTime = _dateTime;
	isClosed = 0;
	sum = _sum;
	userId = _userId;
	debitTypeId = _type;
}

Debt::Debit::Debit(int _id, string _dateTime, bool _isClosed, double _sum, int _userId, int _type) 
{
	id = _id;
	dateTime = _dateTime;
	isClosed = _isClosed;
	sum = _sum;
	userId = _userId;
	debitTypeId = _type;
}

#pragma endregion Debit 

#pragma region Users

Users::Users()
{

}

Users::Users(string _name) { id = UsersRepository::GetInstance()->GetId(), name = _name; }

Users::Users(int _id, string _name) { name = _name; id = _id; }

Users::Users(int _id, string _name, string _password) { id = _id; name = _name; password = _password; }

Users::Users(string _name, string _password) { id = UsersRepository::GetInstance()->GetId();  name = _name; password = _password; }

#pragma endregion Users

#pragma region Wallet

Wallet::Wallet()
{
	id = WalletRepository::GetInstance()->GetId();
	userId = UsersRepository::GetInstance()->GetId(); 
	number = GenerateAccountNumber(userId);
}

Wallet::Wallet(int _userId)

{
	id = WalletRepository::GetInstance()->GetId();
	userId = _userId;
	number = GenerateAccountNumber(userId);
}

Wallet::Wallet(int _id, int _userId, string _number) { id = _id; userId = _userId; number = _number; }

#pragma endregion Wallet

#pragma region UsersInformation
UsersInformation::UsersInformation()
{

}

UsersInformation::UsersInformation(string _name, string _surname, 
	string _patronymic, string _phoneNumber, string _pasportNumber,string _type)
{
	id = UsersInformationRepository::GetInstance()->GetCommonId();
	name = _name;
	surname = _surname;
	patronymic = _patronymic;
	phoneNumber = _phoneNumber;
	pasportNumber = _pasportNumber;
	type = _type;
}

UsersInformation::UsersInformation(int _id, string _name, string _surname,
	string _patronymic, string _phoneNumber, string _pasportNumber, string _type)
{
	id = _id;
	name = _name;
	surname = _surname;
	patronymic = _patronymic;
	phoneNumber = _phoneNumber;
	pasportNumber = _pasportNumber;
	type = _type;
}

#pragma endregion UsersInformation

#pragma region UsersRepository

UsersRepository* UsersRepository::obj = nullptr;

UsersRepository::UsersRepository()
{
	filename = "Users.json";
	obj = this;
	Build();
}

void UsersRepository::Build()
{
	try
	{
		ifstream f(filename);

		json j = json::array();

		j = json::parse(f);

		repository.clear();

		for (int i = 0; i < j.size(); i++) {
			repository.push_back(new Users(j[i]["id"].get<int>(), j[i]["name"].get<string>(), j[i]["password"].get<string>()));
		}

		f.close();
	}
	catch (FileException& fe)
	{
		std::cout << fe.GetValue() << endl;
	}
	catch (exception& ex)
	{
		std::cout << ex.what() << endl;
	}
}

void UsersRepository::UpdateDate()
{
	try
	{
		ofstream f(filename);
		json j = json::array();
		int k = 0;
		for (auto l : repository) {
			j[k]["id"] = l->id;
			j[k]["name"] = l->name;
			j[k]["password"] = l->password;
			k++;
		}
		f << j;
		f.close();
	}
	catch (FileException& fe)
	{
		std::cout << fe.GetValue() << endl;
	}
	catch (exception& ex)
	{
		std::cout << ex.what() << endl;
	}
}

UsersRepository* UsersRepository::GetInstance()
{
	if (obj == nullptr)
		return new UsersRepository();
	return obj;
}

int UsersRepository::GetId() {
	int id = 0;
	if (GetInstance()->repository.size() != 0) {
	  id = GetInstance()->repository.size();
	  
	}
	return id;
}

void UsersRepository::AddUser(Users* nwUser) { repository.push_back(nwUser); }

vector<Users> UsersRepository::GetRepository() {
	vector<Users> nwRep;
	for (auto i : GetInstance()->repository) {
		nwRep.push_back(*i);
	}
	return nwRep;
}

void UsersRepository::ChangePassword(int _userId, string newPassword) 
{
	for (auto i : repository) 
	{
		if (i->id == _userId) 
		{
			i->password = newPassword;
		}
	}
	UpdateDate();
}

#pragma endregion UsersRepository

#pragma region WalletRepository

WalletRepository* WalletRepository::obj = nullptr;

WalletRepository::WalletRepository()
{
	filename = "Wallet.json";
	obj = this;
	Build();
}

void WalletRepository::Build()
{
	try {
		ifstream f(filename);

		json j = json::array();

		j = json::parse(f);

		repository.clear();

		for (int i = 0; i < j.size(); i++) {
			repository.push_back(new Wallet(j[i]["id"].get<int>(), j[i]["userId"].get<int>(), j[i]["number"].get<string>()));
		}

		f.close();
	}
	catch (FileException& fe)
	{
		std::cout << fe.GetValue() << endl;
	}
	catch (exception& ex)
	{
		std::cout << ex.what() << endl;
	}
}

void WalletRepository::UpdateDate()
{
	ofstream f(filename);
	json j = json::array();
	int k = 0;
	for (auto l : repository) {
		j[k]["id"] = l->id;
		j[k]["userId"] = l->userId;
		j[k]["number"] = l->number;
		k++;
	}
	f << j;
	f.close();
}

WalletRepository* WalletRepository::GetInstance()
{
	if (obj == nullptr)
		return new WalletRepository();
	return obj;
}

int WalletRepository::GetId() {
	int id = 0;
	if (GetInstance()->repository.size() != 0) {
		id = GetInstance()->repository.size();

	}
	return id;
}

void WalletRepository::Add(Wallet* nwWallet) { repository.push_back(nwWallet); }

vector<Wallet> WalletRepository::GetRepository() {
	vector<Wallet> nwRep;
	for (auto i : GetInstance()->repository) {
		nwRep.push_back(*i);
	}
	return nwRep;
}

Wallet* WalletRepository::GetWallet(int _userId)
{
	for (auto i : repository)
	{
		if(i->userId==_userId)
		{
			return i;
		}
	}
}

#pragma endregion WalletRepository

#pragma region CreditRepository

CreditRepository* CreditRepository::obj = nullptr;

CreditRepository::CreditRepository()
{
	filename = "Credit.json";
	obj = this;
	Build();
}

void CreditRepository::Build()
{
	try {
		ifstream f(filename);

		json j = json::array();

		j = json::parse(f);

		repository.clear();

		for (int i = 0; i < j.size(); i++) {
			repository.push_back(new Debt::Credit(j[i]["id"].get<int>(), j[i]["dateTime"].get<string>(),
				j[i]["isClosed"].get<bool>(), j[i]["sum"].get<double>(), j[i]["duration"].get<int>(),
				j[i]["userId"].get<int>(), j[i]["interestRate"].get<double>(), j[i]["type"].get<int>()));
		}

		f.close();
	}
	catch (FileException& fe)
	{
		std::cout << fe.GetValue() << endl;
	}
	catch (exception& ex)
	{
		std::cout << ex.what() << endl;
	}
}

void CreditRepository::UpdateDate()
{
	try {
		ofstream f(filename);
		json j = json::array();
		int k = 0;
		for (auto l : repository) {
			j[k]["id"] = l->id;
			j[k]["dateTime"] = l->dateTime;
			j[k]["isClosed"] = l->isClosed;
			j[k]["sum"] = l->sum;
			j[k]["duration"] = l->duration;
			j[k]["userId"] = l->userId;
			j[k]["interestRate"] = l->interestRate;
			j[k]["type"] = l->type;
			k++;
		}
		f << j;
		f.close();
	}
	catch (FileException& fe)
	{
		std::cout << fe.GetValue() << endl;
	}
	catch (exception& ex)
	{
		std::cout << ex.what() << endl;
	}
}

CreditRepository* CreditRepository::GetInstance()
{
	if (obj == nullptr)
		return new CreditRepository();
	return obj;
}

int CreditRepository::GetId() {
	int id = 0;
	if (GetInstance()->repository.size() != 0) {
		id = GetInstance()->repository.size();

	}
	return id;
}

void CreditRepository::Add(Debt::Credit * nwCredit) { repository.push_back(nwCredit); }

vector<Debt::Credit> CreditRepository::GetRepository() {
	vector<Debt::Credit> nwRep;
	for (auto i : GetInstance()->repository) {
		nwRep.push_back(*i);
	}
	return nwRep;
}

void CreditRepository::CloseCredit(int _id) 
{
	for (auto i : repository) 
	{
		if (i->id == _id) 
		{
			i->isClosed = 1;
		}
	}
	UpdateDate();
}
#pragma endregion CreditRepository

#pragma region DebitRepository

DebitRepository* DebitRepository::obj = nullptr;

DebitRepository::DebitRepository()
{
	filename = "Debit.json";
	obj = this;
	Build();
}

void DebitRepository::Build()
{
	try {
		ifstream f(filename);

		json j = json::array();

		j = json::parse(f);

		repository.clear();

		for (int i = 0; i < j.size(); i++) {
			repository.push_back(new Debt::Debit(j[i]["id"].get<int>(), j[i]["dateTime"].get<string>(),
				j[i]["isClosed"].get<bool>(), j[i]["sum"].get<double>(), j[i]["userId"].get<int>(),
				j[i]["debitTypeId"].get<int>()));
		}

		f.close();
	}
	catch (FileException& fe)
	{
		std::cout << fe.GetValue() << endl;
	}
	catch (exception& ex)
	{
		std::cout << ex.what() << endl;
	}
}

void DebitRepository::UpdateDate()
{
	try {
		ofstream f(filename);
		json j = json::array();
		int k = 0;
		for (auto l : repository) {
			j[k]["id"] = l->id;
			j[k]["dateTime"] = l->dateTime;
			j[k]["isClosed"] = l->isClosed;
			j[k]["sum"] = l->sum;
			j[k]["userId"] = l->userId;
			j[k]["debitTypeId"] = l->debitTypeId;
			k++;
		}
		f << j;
		f.close();
	}
	catch (FileException& fe)
	{
		std::cout << fe.GetValue() << endl;
	}
	catch (exception& ex)
	{
		std::cout << ex.what() << endl;
	}
}

DebitRepository* DebitRepository::GetInstance()
{
	if (obj == nullptr)
		return new DebitRepository();
	return obj;
}

int DebitRepository::GetId() {
	int id = 0;
	if (GetInstance()->repository.size() != 0) {
		id = GetInstance()->repository.size();

	}
	return id;
}

void DebitRepository::Add(Debt::Debit* nwDebit) { repository.push_back(nwDebit); }

vector<Debt::Debit> DebitRepository::GetRepository() {
	vector<Debt::Debit> nwRep;
	for (auto i : GetInstance()->repository) {
		nwRep.push_back(*i);
	}
	return nwRep;
}

void DebitRepository::CloseDebit(int _id)
{
	for (auto i : repository)
	{
		if (i->id == _id)
		{
			i->isClosed = 1;
		}
	}
	UpdateDate();
}
#pragma endregion DebitRepository

#pragma region DebitTypeRepository

DebitTypeRepository* DebitTypeRepository::obj = nullptr;

DebitTypeRepository::DebitTypeRepository()
{
	filename = "DebitType.json";
	obj = this;
	Build();
}

void DebitTypeRepository::Build()
{
	try {
		ifstream f(filename);

		json j = json::array();

		j = json::parse(f);

		repository.clear();

		for (int i = 0; i < j.size(); i++) 
		{
			repository.push_back(new DebitType(j[i]["id"].get<int>(), j[i]["name"].get<string>(),
				j[i]["minSum"].get<double>(), j[i]["duration"].get<double>(), j[i]["interestRate"].get<double>()));
		}

		f.close();
	}
	catch (FileException& fe)
	{
		std::cout << fe.GetValue() << endl;
	}
	catch (exception& ex)
	{
		std::cout << ex.what() << endl;
	}
}

DebitTypeRepository* DebitTypeRepository::GetInstance()
{
	if (obj == nullptr)
		return new DebitTypeRepository();
	return obj;
}

vector<DebitType> DebitTypeRepository::GetRepository() {
	vector<DebitType> nwRep;
	for (auto i : GetInstance()->repository) {
		nwRep.push_back(*i);
	}
	return nwRep;
}

void DebitTypeRepository::UpdateDate()
{
	try {
		ofstream f(filename);
		json j = json::array();
		int k = 0;
		for (auto l : repository) {
			j[k]["id"] = l->id;
			j[k]["name"] = l->name;
			j[k]["minSum"] = l->minSum;
			j[k]["duration"] = l->duration;
			j[k]["interestRate"] = l->interestRate;
			k++;
		}
		f << j;
		f.close();
	}
	catch (FileException& fe)
	{
		std::cout << fe.GetValue() << endl;
	}
	catch (exception& ex)
	{
		std::cout << ex.what() << endl;
	}
}

DebitType DebitTypeRepository::GetType(int _id) 
{
	DebitType db;
	for (auto i : repository) 
	{
		if (i->id == _id) db = *i;
	}
	return db;
}

#pragma endregion DebitTypeRepository

#pragma region UsersInformationRepository

UsersInformationRepository* UsersInformationRepository::obj = nullptr;

UsersInformationRepository::UsersInformationRepository()
{
	filename = "UsersInformation.json";
	obj = this;
	Build();
}

void UsersInformationRepository::Build()
{
	ifstream f(filename);

	json j = json::array();

	j = json::parse(f);

	repository.clear();
	for (int i = 0; i < j.size(); i++) {
		repository.push_back(new UsersInformation(j[i]["id"].get<int>(),
			j[i]["name"].get<string>(), j[i]["surname"].get<string>(), 
			j[i]["patronymic"].get<string>(), j[i]["phoneNumber"].get<string>(), 
			j[i]["pasportNumber"].get<string>(), j[i]["type"].get<string>()));
	}

	f.close();
}

void UsersInformationRepository::UpdateDate()
{
	ofstream f(filename);
	json j = json::array();
	int k = 0;
	for (auto l : repository) {
		j[k]["id"] = l->id;
		j[k]["name"] = l->name;
		j[k]["surname"] = l->surname;
		j[k]["patronymic"] = l->patronymic;
		j[k]["phoneNumber"] = l->phoneNumber;
		j[k]["pasportNumber"] = l->pasportNumber;
		j[k]["type"] = l->type;
		k++;
	}
	f << j;
	f.close();
}

UsersInformationRepository* UsersInformationRepository::GetInstance()
{
	if (obj == nullptr)
		return new UsersInformationRepository();
	return obj;
}

int UsersInformationRepository::GetCommonId() {
	int id = 0;
	if (GetInstance()->repository.size() != 0) {
		id = GetInstance()->repository.size();

	}
	return id;
}

void UsersInformationRepository::AddInformation(UsersInformation* nwUsersAccount) { repository.push_back(nwUsersAccount); }

vector<UsersInformation> UsersInformationRepository::GetRepository() {
	vector<UsersInformation> nwRep;
	for (auto i : GetInstance()->repository) {
		nwRep.push_back(*i);
	}
	return nwRep;
}

void UsersInformationRepository::Edit(int _id, string _name, string _surname, string _patronymic, string _phoneNumber) 
{
	repository[_id]->name = _name;
	repository[_id]->surname = _surname;
	repository[_id]->patronymic = _patronymic;
	repository[_id]->phoneNumber = _phoneNumber;
	UpdateDate();
}

#pragma endregion UsersInformationRepository

#pragma region Bank

Bank::Bank() 
{
	usersRepository = UsersRepository::GetInstance();
	walletRepository = WalletRepository::GetInstance();
	usersInformationRepository = UsersInformationRepository::GetInstance();
	paymentRepository = PaymentRepository::GetInstance();
	creditRepository = CreditRepository::GetInstance();
	bankStatus = new BankStatus();
	debitRepository = DebitRepository::GetInstance();
	debitTypeRepository = DebitTypeRepository::GetInstance();
}

int Bank::SignIn(string login, string name, string surname, string patronymic, string phoneNumber, string pasportNumber, string type, string password)
{
	if (IsValidUser(login, pasportNumber)) {}
	else return -1; //make exception
	Users *nwUser = new Users(login, Hashing(password));
	usersRepository->AddUser(nwUser);
	usersRepository->UpdateDate();
	Wallet* nwWallet = new Wallet(nwUser->id);
	walletRepository->Add(nwWallet);
	walletRepository->UpdateDate();
	UsersInformation* nwUsersInformation = new UsersInformation(name, surname, patronymic, phoneNumber, pasportNumber, type);
	usersInformationRepository->AddInformation(nwUsersInformation);
	usersInformationRepository->UpdateDate();
}

int Bank::IsValidUser(string login, string pasportNumber) 
{
	Bank();
	for (auto i : usersRepository->GetRepository()) {
		if (i.name == login) return 2;
	}
	for (auto i : usersInformationRepository->GetRepository()) {
		if (i.pasportNumber == pasportNumber) return 0;
	}
	return 1;
}

int Bank::GetIn(string login, string password)
{
	for (auto i : usersRepository->GetRepository())
	{
		if (i.name == login) 
		{
			if (i.password == Hashing(password)) {
				return i.id;
			}
		}
	}
	cout << "Wrong login or password" << endl;
	return -1;
}

void Bank::PrintUsers() {
	for (auto i : usersRepository->GetRepository()) {
		cout << i.id << " " << i.name << endl;
	}
}

Payment* Bank::CreatePayment(int _userId, double _amount, BalanceOperationType b)
{
	Wallet* w = walletRepository->GetWallet(_userId);
	Payment* p = new Payment();
	p->id = paymentRepository->GetId();
	p->amount = _amount;
	p->walletId = w->id;
	p->balanceOperationType = b;
	p->dateTime = DateTimeToString(DateTimeNow());

	paymentRepository->Add(p);
	paymentRepository->UpdateDate();
	return p;
}

double Bank::GetBalance(int _walletId)
{
	double balance = 0;
	for (auto i : paymentRepository->GetRepository()) 
	{
		if (i.walletId == _walletId) {
			if (i.balanceOperationType == Credit)
			{
				balance -= i.amount;
			}
			if (i.balanceOperationType == Debit) 
			{
				balance += i.amount;
			}
		}
	}
	return balance;
}

string Bank::GetWalletNumber(int _userId) 
{
	return walletRepository->GetWallet(_userId)->number;
}

void Bank::EditInformation(int _userId) 
{
	vector<UsersInformation> rep = usersInformationRepository->GetRepository();
	cout << "Your old data\nName: " << rep[_userId].name << "\nSurname: " << rep[_userId].surname << "\nPatronymic: " << rep[_userId].patronymic << "\nphoneNumber: " << rep[_userId].phoneNumber << endl;
	cout << "Do you wanna to change name(y/n)" << endl;
	string name;
	string surname;
	string patronymic;
	string phoneNumber;
	char ch;
	ch = _getch();
	if (ch == 'y')
	{
		cout << "Enter: " << endl;
		cin >> name;
	}
	else name = rep[_userId].name;
	cout << "Do you wanna to change surname(y/n)" << endl; 
	ch = _getch();
	if (ch == 'y')
	{
		cout << "Enter: " << endl;
		cin >> surname;
	}
	else surname = rep[_userId].surname;
	cout << "Do you wanna to change patronymic(y/n)" << endl;
	ch = _getch();
	if (ch == 'y')
	{
		cout << "Enter: " << endl;
		cin >> patronymic;
	}
	else patronymic = rep[_userId].patronymic;
	cout << "Do you wanna to change phone number(y/n)" << endl;
	ch = _getch();
	if (ch == 'y')
	{
		cout << "Enter: " << endl;
		cin >> phoneNumber;
	}
	else phoneNumber = rep[_userId].phoneNumber;
	cout << "Do you wanna to save edits without returning? (y/n)" << endl;
	ch = _getch();
	if (ch == 'y') {
		usersInformationRepository->Edit(_userId, name, surname, patronymic, phoneNumber);
	}
	else return;

}

void Bank::ShowInformation(int _userId) 
{
	vector<UsersInformation> rep = usersInformationRepository->GetRepository();
	cout << "Name: " << rep[_userId].name 
		<< "\nSurname: " << rep[_userId].surname 
		<< "\nPatronymic: " << rep[_userId].patronymic 
		<< "\nphoneNumber: " << rep[_userId].phoneNumber 
		<< "\nPassport Number: " << rep[_userId].pasportNumber 
		<< "\nType: " <<rep[_userId].type << endl;
}

bool Bank::Transaction(int _userIdFrom, string _walletNumberTo, double _amount)
{
	if (GetBalance(_userIdFrom) < _amount)
	{
		cout << "There aren't enought money on balance" << endl;
		return 0;
	}

	int userIdTo =-1;
	for (auto i : walletRepository->GetRepository()) 
	{
		if(i.number == _walletNumberTo)
		{
			userIdTo = i.userId;
		}
	}
	if (userIdTo == -1)
		return 0;
	
	CreatePayment(_userIdFrom, _amount, Credit);
	CreatePayment(userIdTo, _amount, Debit);
	return 1;
}

void Bank::EditPassword(int _userId, string oldPassword, string newPassword) 
{
	for (auto i : usersRepository->GetRepository())
	{
		if (i.id == _userId)
		{
			if (i.password == Hashing(oldPassword)) 
			{
				i.password = Hashing(newPassword);
			}
			else 
			{
				cout << "Wrong old password" << endl;
				return;
			}
		}
	}
	usersRepository->ChangePassword(_userId, Hashing(newPassword));

}

Vector<CreditPayment> Bank::CalculateCreditPayment(Debt::Credit& credit)
{
	Vector<CreditPayment> rep;
	if (credit.type==0)
	{
		int duration = credit.duration;
		double sum = credit.sum;
		double rate = credit.interestRate/((double)duration*100);
		double paymentSum = sum*(rate + (rate/(pow((1+rate), duration)-1)) );
		double perc;
		double dolg;
		for (int i = 0; i < credit.duration; i++) 
		{
			CreditPayment crp;
			perc = sum * rate;
			dolg = paymentSum - perc;
			crp.id = i;
			crp.sum = dolg;
			crp.percentages = perc;
			rep.push_back(crp);
			sum -= paymentSum;
		}
		return rep;
	}
	if (credit.type==1) 
	{
		int duration = credit.duration;
		double sum = credit.sum;
		double rate = credit.interestRate / ((double)duration * 100);
		double b = sum / duration;
		double perc;
		for (int i = 0; i < credit.duration; i++) 
		{
			CreditPayment crp;
			crp.id = i;
			perc = sum * rate;
			crp.percentages = perc;
			crp.sum = b;
			rep.push_back(crp);
			sum = sum - (b + perc);
		}
		return rep;
	}
}

double Bank::ActualCreditPayment(int _userId, int _walletId) 
{
	bool flag = 0;
	Vector<CreditPayment> rep;
	DateTime creditTime;
	int creditId;
	for(auto i: creditRepository->GetRepository())
	{
		if (i.userId == _userId && i.isClosed == 0) 
		{
			creditTime = DateTimeParse(i.dateTime);
			rep = CalculateCreditPayment(i);
			creditId = i.id;
			flag = 1;
		}
	}

	if (flag == 0) return 0;

	int countOfPayment = 0;
	flag = 0;
	int count=0;
	for (auto i : paymentRepository->GetRepository()) 
	{
		if (flag && i.walletId == 0 && i.balanceOperationType == Debit&&i.amount==(rep[count].sum+ rep[count].percentages))
		{
			count++;
		}
		flag = 0;
		if ((DateTimeCompare(creditTime, DateTimeParse(i.dateTime)) != 0)&&i.walletId==_walletId&&i.balanceOperationType==Credit)
		{
			flag = 1;
		}
	}
	if (rep.size() == count) 
	{
		creditRepository->CloseCredit(creditId);
		return 0;
	}
	return rep[count].sum + rep[count].percentages;
}

bool Bank::OpenCredit(double _sum, int _duration, int _userId, int type)
{
	for (auto i : creditRepository->GetRepository())
	{
		if (i.userId == _userId && i.isClosed == 0)
		{
			return 0;
		}
	}
	if (bankStatus->GetBalance() < _sum) return 0;

	int id = creditRepository->GetId();
	double interestRate = bankStatus->GetInterestRate();

	creditRepository->Add(new Debt::Credit(id, DateTimeToString(DateTimeNow()), 0, _sum, _duration, _userId, interestRate, type));
	creditRepository->UpdateDate();
	bankStatus->TakeCredit(_sum);
	CreatePayment(_userId, _sum, Debit);
}

void Bank::MonthlyPayment(int _userId) 
{
	double sum = ActualCreditPayment(_userId, walletRepository->GetWallet(_userId)->id);
	if(sum==0)
	{
		cout << "You don't need make payment" << endl;
		return;
	}
	cout << "Do you wanna make payment now?(y/n)" << endl << "Sum: " << sum << endl;
	char ch = _getch();
	if (ch == 'y') 
	{
		if (Transaction(_userId, BankAccountNumber, sum))
		{
			bankStatus->AddToBankBalance(sum);
			cout << "Successfully" << endl;
		}
		else cout << "Not successfully" << endl;
	}
}

void Bank::CreditInformation(int _userId) 
{
	int _walletId = walletRepository->GetWallet(_userId)->id;
	double sum = ActualCreditPayment(_userId, _walletId);
	if (sum == 0)
	{
		cout << "You don't have any credits" << endl;
		return;
	}
	bool flag = 0;
	Vector<CreditPayment> rep;
	DateTime creditTime;
	int creditId;
	for (auto i : creditRepository->GetRepository())
	{
		if (i.userId == _userId && i.isClosed == 0)
		{
			creditTime = DateTimeParse(i.dateTime);
			rep = CalculateCreditPayment(i);
			creditId = i.id;
			flag = 1;
		}
	}

	int countOfPayment = 0;
	flag = 0;
	int count = 0;
	for (auto i : paymentRepository->GetRepository())
	{
		if (flag && i.walletId == 0 && i.balanceOperationType == Debit && i.amount == (rep[count].sum + rep[count].percentages))
		{
			count++;
		}
		flag = 0;
		if ((DateTimeCompare(creditTime, DateTimeParse(i.dateTime)) != 0) && i.walletId == _walletId && i.balanceOperationType == Credit)
		{
			flag = 1;
		}
	}
	cout << "Yoy must pay " << rep.size() - count << " times: " << endl;
	for (int i = count; i < rep.size(); i++) 
	{
		cout << i + 1 << "." << rep[i].sum + rep[i].percentages << endl;
	}
}

double Bank::GetRate() { return bankStatus->GetInterestRate(); }

vector<int> Bank::ShowDebitTypes(double _sum, int maxDuration) 
{
	vector<int> gd;
	for (auto i : debitTypeRepository->GetRepository()) 
	{
		if (i.minSum <= _sum && i.duration <= maxDuration) {
			cout << "| " << setw(4) << i.id + 1 << ". " << setw(20) << i.name << " ,minimum amount: " << setw(10) << i.minSum << " ,with interest rate: " << setw(5) << i.interestRate << " , duration: " << setw(8) << i.duration << " months |" << endl;
			cout << "_________________________________________________________________________________________________________________" << endl;
			gd.push_back(i.id);
		}
	}
	return gd;
}

bool Bank::OpenDebit(int _userId, double _sum, int maxDuration)
{
	vector<int> gd = ShowDebitTypes(_sum, maxDuration);
	cout << "Enter a number of the type of debit" << endl;
	int id;
	cin >> id;
	id--;
	system("cls");
	bool fl = 0;
	for (auto i : gd) 
	{
		if (i == id) fl = 1;
	}
	if(fl == 0)
	{
		cout << "Bad input" << endl;
		_getch();
		system("cls");
		return 0;
	}
	cout << "Are you sure?(y/n)" << endl;
	char ch = _getch();
	system("cls");
	switch (ch) 
	{
	case 'y': 
	{
		if (Transaction(_userId, BankAccountNumber, _sum)) {
			debitRepository->Add(new Debt::Debit(DateTimeToString(DateTimeNow()), _sum, _userId, id));
			debitRepository->UpdateDate();
			bankStatus->AddToBankBalance(_sum);
			return 1;
		}
		else 
		{
			cout << "Error" << endl;
			_getch();
			system("cls");
			return 0;
		}
	}
	default: {return 0; }
	}
}

void Bank::DebitInformation(int _userId) 
{
	ActualDebit(_userId);
	bool fl = 0;
	int k = 1;
	for (auto i : debitRepository->GetRepository()) 
	{
		if (i.userId == _userId&&i.isClosed == 0) 
		{
			if (fl == 0) 
			{
				cout << "Your debits: " << endl;
				fl = 1;
			}
			cout << setw(4) << k++ << ". " << setw(15) << debitTypeRepository->GetType(i.debitTypeId).name << setw(6)
				<< " ,amount: " << setw(10) << i.sum << " ,time: " <<setw(18) << i.dateTime << " ,duration: " << setw(5)
				<< debitTypeRepository->GetType(i.debitTypeId).duration << " months, with interest rate: " 
				<< setw(5) << debitTypeRepository->GetType(i.debitTypeId).interestRate << " |" << endl;
			cout << "________________________________________________________________________________________________________________________" << endl;
		}
	}
	if (fl == 0) 
	{
		cout << "There isn't any debits" << endl;
	}
}

void Bank::ActualDebit(int _userId) 
{
	vector<Debt::Debit> rep;
	for (auto i : debitRepository->GetRepository()) 
	{
		if (i.userId == _userId) 
		{
		if(  DateTimeCompareDebit(DateTimeNow(), DateTimeParse(i.dateTime), debitTypeRepository->GetType( i.debitTypeId).duration)!=2)
		{
			debitRepository->CloseDebit(i.id);
			CreatePayment(_userId, i.sum*(debitTypeRepository->GetType(i.debitTypeId).interestRate/100+1), Debit);
			bankStatus->SubBalance(i.sum * (debitTypeRepository->GetType(i.debitTypeId).interestRate / 100 + 1));
		}
		}
	}
}

#pragma endregion Bank

#pragma region ActualUser

ActualUser::ActualUser()
{
	try {
		ifstream f("ActualUser.json");

		json j = json::array();

		j = json::parse(f);


		id = j["id"].get<int>();
		login = j["login"].get<string>();
		pin = j["pin"].get<int>();

		f.close();
	}
	catch (FileException& fe)
	{
		std::cout << fe.GetValue() << endl;
	}
	catch (exception& ex)
	{
		std::cout << ex.what() << endl;
	}
}

bool IsEmptyActual() 
{
	ifstream f("ActualUser.json");
	return f.peek() == ifstream::traits_type::eof();
}

ActualUser::ActualUser(int _id, string _login, int _pin)
{
	id = _id;
	login = _login;
	pin = _pin;
	ofstream f;
	f.open("ActualUser.json", ofstream::out | ofstream::trunc);
	json j;
	j["id"] = id;
	j["login"] = login;
	j["pin"] = pin;
	f << j;
	f.close();
}

string ActualUser::GetLogin() 
{
	return login;
}

int ActualUser::GetId() 
{
	return id;
}

bool ActualUser::IsRightPin(int _pin)
{
	return pin == _pin;
}

void ActualUser::Erase() 
{
	ofstream f;
	f.open("ActualUser.json", ofstream::out | ofstream::trunc);
	f.close();
}

#pragma endregion ActualUser

#pragma region Payment

Payment::Payment() {}

Payment::Payment(int _id, int _walletId, double _amount, BalanceOperationType _balanceOperationType, string _dateTime)
{
	id = _id;
	walletId = _walletId;
	amount = _amount;
	balanceOperationType = _balanceOperationType;
	dateTime = _dateTime;
}

#pragma endregion Payment

#pragma region PaymentRepository
PaymentRepository* PaymentRepository::obj = nullptr;

PaymentRepository::PaymentRepository()
{
	filename = "Payment.json";
	obj = this;
	Build();
}

void PaymentRepository::Build()
{
	try {
		ifstream f(filename);

		json j = json::array();

		j = json::parse(f);

		repository.clear();

		for (int i = 0; i < j.size(); i++) {
			int _id = j[i]["id"].get<int>();
			int _walletId = j[i]["walletId"].get<int>();
			double _amount = j[i]["amount"].get<double>();
			BalanceOperationType _bal = static_cast<BalanceOperationType>(j[i]["balanceOperationType"].get<int>());
			string _dateTime = j[i]["dateTime"].get<string>();
			repository.push_back(new Payment(_id, _walletId, _amount, _bal, _dateTime));
		}

		f.close();
	}
	catch (FileException& fe)
	{
		std::cout << fe.GetValue() << endl;
	}
	catch (exception& ex)
	{
		std::cout << ex.what() << endl;
	}
}

void PaymentRepository::UpdateDate()
{
	try
	{
		ofstream f(filename);
		json j = json::array();
		int k = 0;
		for (auto l : repository) {
			j[k]["id"] = l->id;
			j[k]["walletId"] = l->walletId;
			j[k]["amount"] = l->amount;
			j[k]["balanceOperationType"] = (int)l->balanceOperationType;
			j[k]["dateTime"] = l->dateTime;
			k++;
		}
		f << j;
		f.close();
	}
	catch (FileException& fe)
	{
		std::cout << fe.GetValue() << endl;
	}
	catch (exception& ex)
	{
		std::cout << ex.what() << endl;
	}
}

PaymentRepository* PaymentRepository::GetInstance()
{
	if (obj == nullptr)
		return new PaymentRepository();
	return obj;
}

int PaymentRepository::GetId() {
	int id = 0;
	if (GetInstance()->repository.size() != 0) {
		id = GetInstance()->repository.size();

	}
	return id;
}

vector<Payment> PaymentRepository::GetRepository() {
	vector<Payment> nwRep;
	for (auto i : GetInstance()->repository) {
		nwRep.push_back(*i);
	}
	return nwRep;
}

void PaymentRepository::Add(Payment* nwPayment) { repository.push_back(nwPayment); }

#pragma endregion PaymentRepository 

#pragma region Exception
FileException::FileException(const char* msg, string value) : exception(msg)
{
	this->value = value;
}

string FileException::GetValue()
{
	return value;
}

#pragma endregion Exception

#pragma region BankStatus

BankStatus::BankStatus()
{
	try {
		ifstream f("BankStatus.json");

		json j = json::array();

		j = json::parse(f);


		balance = j["balance"].get<double>();
		interestRate = j["interestRate"].get<double>();

		f.close();
	}
	catch (FileException& fe) 
	{
		std::cout << fe.GetValue()<<endl;
	}
	catch (exception& ex) 
	{
		std::cout << ex.what() << endl;
	}
}

BankStatus::BankStatus(double _balance, double _interestRate)
{
	try {
		balance = _balance;
		interestRate = _interestRate;
		ofstream f;
		f.open("BankStatus.json", ofstream::out | ofstream::trunc);
		json j;
		j["balance"] = balance;
		j["interestRate"] = interestRate;
		f << j;
		f.close();
	}
	catch (FileException& fe)
	{
		std::cout << fe.GetValue() << endl;
	}
	catch (exception& ex)
	{
		std::cout << ex.what() << endl;
	}
}

double BankStatus::GetBalance()
{
	return balance;
}

double BankStatus::GetInterestRate()
{
	return interestRate;
}

void BankStatus::AddToBankBalance(double amount)
{
	balance += amount;
	UpdateDate();
}

bool BankStatus::TakeCredit(double amount) 
{
	if (balance < amount) return 0;
	balance -= amount;
	UpdateDate();
	return 1;
}

void BankStatus::UpdateDate()
{
	try {
		ofstream f("BankStatus.json");
		json j;

		j["balance"] = balance;
		j["interestRate"] = interestRate;

		f << j;
		f.close();
	}
	catch (FileException& fe)
	{
		std::cout << fe.GetValue() << endl;
	}
	catch (exception& ex)
	{
		std::cout << ex.what() << endl;
	}
}

void BankStatus::SubBalance(double amount) 
{
	balance -= amount;
	UpdateDate();
}

#pragma endregion BankStatus

#pragma region DateTime 

DateTime::DateTime() {}

DateTime::DateTime(int _day, int _month, int _year, int _hour, int _minute, int _second) 
{
	day = _day;
	month = _month;
	year = _year;
	hour = _hour;
	minute = _minute;
	second = _second;
}

#pragma endregion DateTime


ActualUser& Start(Bank& bank) 
{
	if (IsEmptyActual() == false) {
		ActualUser actUser;
		cout << "Do you wanna to continue as " << actUser.GetLogin() << "?\n1 - yes\n2 - no" << endl;
		int a;
		cin >> a;
		switch (a) 
		{
		case 1: 
		{
			string pass;
			cout << "Enter your pin" << endl;
			int ch = 0;
			int count2 = 3;
			while (count2--) {
				pass.clear();
				int count = 4;
				while (count--)
				{
					ch = _getch();
					if (ch == 13)//enter
					{
						break;
					}
					if (ch == 27)//escape
					{
						exit(0);
					}
					if (ch == 8)//backspace
					{
						count++;
						cout << (char)8 << ' ' << char(8);

						if (!pass.empty())

							pass.erase(pass.length() - 1);
					}

					else
					{
						cout << '*';
						pass += (char)ch;
					}
				}
				if (actUser.IsRightPin(stoi(pass)))
				{

					cout << "\n Pin is good\n" << endl;
					return actUser;
				}
				else
				{
					cout << "\nBad pin, try again" << endl;
				}
			}
			actUser.Erase();
			break;
		}
		default: 
		{
			actUser.Erase();
			break;
		}
		}
	}
	cout << "1 - sign in\n2 - get in" << endl;
	int a;
	cin >> a;
	switch (a) 
	{
	case 1: 
	{
		bool bad = 1;
		string login;
		cout << "Enter login: " << endl;
		cin >> login;
		string name;
		cout << "Enter name: " << endl;
		cin >> name;
		string surname;
		cout << "Enter surname: " << endl;
		cin >> surname;
		string patronymic;
		cout << "Enter patronymic: " << endl;
		cin >> patronymic;
		string phoneNumber;
		cout << "Enter phone number: " << endl;
		cin >> phoneNumber;
		string pasportNunmber;
		cout << "Enter passport number: " << endl;
		cin >> pasportNunmber;
		string type;
		cout << "Choose your type: \n1 - private person\n2 - legal entity\n3 - beneficiary" << endl;
		int h;
		cin >> h;
		switch (h)
		{
		case 1: 
		{
			type = "PrivarePerson";
			break;
		}
		case 2: 
		{
			type = "LegalEntity";
			break;
		}
		case 3: 
		{
			type = "Beneficiary";
			break;
		}
		default: 
		{
			bad = 1;
			break;
		}
		}
		string password;
		cout << "Enter password: " << endl;
		cin >> password;


		int l = bank.SignIn(login, name, surname, patronymic, phoneNumber, pasportNunmber, type, password);
		if (l == -1) 
		{
			cout << "Login or passport number error" << endl;
			exit(1);
		}
		int pin;
		cout << "Enter 4 number for pin" << endl;
		cin >> pin;
		ActualUser actUser(bank.usersRepository->GetId()-1, login, pin);
		return actUser;
		break;
	}
	case 2: 
	{
		cout << "Enter login: " << endl;
		string login;
		cin >> login;
		cout << "Enter password: " << endl;
		string password;
		cin >> password;
		int id = bank.GetIn(login, password);
		if (id == -1)
		{
			cout << "Bad login or password" << endl;
			exit(1);
		}
		int pin;
		cout << "Enter 4 number for pin" << endl;
		cin >> pin;
		ActualUser actUser(id, login, pin);
		return actUser;
	}
	default: 
	{
		break;
	}
	}
	exit(1);
}

int main()
{
	Bank bank;
	ActualUser actUser = Start(bank);
	while (true) {
		cout << "1 - Setting\n2 - Information\n3 - Finance\n4 - Debit/Credit\n5 - Information\n6 - Exit" << endl;
		char ch = _getch();
		std::system("cls");
		switch (ch)
		{
		case '1':
		{
			cout << "1 - Edit your information\n2 - Change password\n3 - Exit from account\n4 - Back" << endl;
			char ch1 = _getch();
			std::system("cls");
			switch (ch1)
			{
			case '1':
			{
				bank.EditInformation(actUser.GetId());
				std::system("cls");
				break;
			}
			case '2':
			{
				string oldPassword;
				string newPassword;
				cout << "Enter old password: " << endl;
				cin >> oldPassword;
				std::system("cls");
				cout << "Enter new password: " << endl;
				cin >> newPassword;
				std::system("cls");
				bank.EditPassword(actUser.GetId(), oldPassword, newPassword);
				break;
			}
			case '3':
			{
				actUser.Erase();
				exit(0);
			}
			default: {break; }
			}
			break;
		}
		case '2':
		{
			cout << "1 - Show your information\n2 - Show wallet number\n3 - Back" << endl;
			char ch1 = _getch();
			std::system("cls");
			switch (ch1)
			{
			case '1':
			{
				bank.ShowInformation(actUser.GetId());
				_getch();
				std::system("cls");
				break;
			}
			case '2':
			{
				cout << bank.GetWalletNumber(actUser.GetId()) << endl;
				_getch();
				std::system("cls");
				break;
			}
			default: {break; }
			}
			break;
		}
		case '3':
		{
			cout << "1 - Show balance\n2 - Make payment\n3 - Make transaction\n4 - Back" << endl;
			char ch1 = _getch();
			std::system("cls");
			switch (ch1)
			{
			case '1':
			{
				cout << bank.GetBalance(actUser.GetId()) << endl;
				_getch();
				std::system("cls");
				break;
			}
			case '2':
			{
				cout << "Enter the type of operation\n1 - Debit\n2 - Credit" << endl;
				char ch2 = _getch();
				std::system("cls");
				switch (ch2)
				{
				case '1':
				{
					cout << "Enter an amount of debit" << endl;
					double debit;
					cin >> debit; 
					std::system("cls");
					if (debit < 0) 
					{
						cout << "Bad input" << endl;
						_getch();
						std::system("cls");
						break;
					}
					bank.CreatePayment(actUser.GetId(), debit, Debit);
					break;
				}
				case '2':
				{
					cout << "Enter an amount of credit" << endl;
					double credit;
					cin >> credit;
					std::system("cls");
					if (credit < 0)
					{
						cout << "Bad input" << endl;
						_getch();
						std::system("cls");
						break;
					}
					

					if (credit > bank.GetBalance(actUser.GetId()))
					{
						cout << "Error! Credit more than balance" << endl;
						_getch();
						std::system("cls");
						break;
					}

					bank.CreatePayment(actUser.GetId(), credit, Credit);
					break;
				}
				default: {break; }
				}
				break;
			}
			case '3':
			{
				cout << "Enter a number of wallet to send the money to" << endl;
				string walletNumberTo;
				cin >> walletNumberTo;
				std::system("cls");

				cout << "Enter a amount" << endl;
				double _amount;
				cin >> _amount;
				std::system("cls");
				if (_amount < 0) 
				{
					cout << "Bad input" << endl;
					_getch();
					std::system("cls");
					break;
				}

				bank.Transaction(actUser.GetId(), walletNumberTo, _amount);
				break;
			}
			default: {break; }
			}
			break;
		}
		case '4':
		{
			cout << "1 - Show information about credit\n2 - Make a monthly payment\n3 - Open a credit\n4 - Show information about your debit\n5 - Open debit\n6 - Debit types\n7 - Back" << endl;
			char ch1 = _getch();
			std::system("cls");
			switch (ch1) 
			{
			case '1': 
			{
				bank.CreditInformation(actUser.GetId());
				_getch();
				std::system("cls");
				break;
			}
			case '2':
			{
				bank.MonthlyPayment(actUser.GetId());
				_getch();
				std::system("cls");
				break;
			}
			case '3':
			{
				double sum;
				int duration;
				int type =0;

				cout << "Enter the amount for which you wanna take out a credit: " << endl;
				cin >> sum;
				std::system("cls");
				if (sum < 0)
				{
					cout << "Bad input" << endl;
					break;
				}

				cout << "Enter a duration in months" << endl;
				cin >> duration;
				std::system("cls");
				if (duration < 0)
				{
					cout << "Bad input" << endl;
					break;
				}

				cout << "Choose a type of credit 1 - Annuity, 2 - differentiated" << endl;
				char ch2 = _getch();
				std::system("cls");
				switch (ch2) 
				{
				case '1': 
				{
					type = 0;
					break;
				}
				case '2':
				{
					type = 1;
					break;
				}
				default: {break; }
				}

				cout << "Do you wanna take a credit for the amount of " << sum << " with duration " << duration << " months?\nContinue?(y/n)" << endl;
				char ch3 = _getch();
				std::system("cls");
				switch (ch3) 
				{
				case 'y':
				{
					if(bank.OpenCredit(sum, duration, actUser.GetId(), type)) cout<<"Successfuly"<<endl;
					_getch();
					std::system("cls");
					break;
				}
				default: {break; }
				}
				break;
			}
			case '4': 
			{
				bank.DebitInformation(actUser.GetId());
				_getch();
				system("cls");
				break;
			}
			case '5':
			{
				double sum;
				double duration;

				cout << "Enter sum to debit" << endl;
				cin >> sum;
				if (sum < 0) { break; }
				std::system("cls");
				cout << "Enter max duration of debit in months" << endl;
				cin >> duration;
				system("cls");
				if (duration < 0) { break;}
				system("cls");
				if (bank.OpenDebit(actUser.GetId(), sum, duration))
				{
					cout << "Successfuly" << endl;
					_getch();
					system("cls");
				}
				break;
			}
			case '6': 
			{
				bank.ShowDebitTypes(INT16_MAX, INT16_MAX);
				_getch();
				system("cls");
			}
			default: {break; }
			}

			break;
		}
		case '5':
		{
			std::system("cls");
			cout << setw(50) << "Welcome" << endl<<endl<<endl<<setw(90) << "    You have made the right choice by using our banking system. This bank offers interest-free transfers,\n" << setw(70) << "profitable loans, and a user-friendly interface.\n\n" << setw(65) << "At the moment, the interest rate:"
				<<bank.GetRate()<<endl;
			_getch();
			std::system("cls");
			break;
		}
		case '6':
		{
			return 0;
		}
		default:
			break;
		}
	}
	return 0;
}
