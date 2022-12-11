#pragma once
#include <string>
class Wallet {

public:

	int id;

	int userId;

	std::string number;

	Wallet();

	Wallet(int _id, int _userId, std::string _number);

	Wallet(int _userId);

};