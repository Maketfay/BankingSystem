#pragma once
#include <string>
class ActualUser 
{
private:

	int id;

	std::string login;

	int pin;

public:

	ActualUser();

	ActualUser(int id, std::string login, int pin);

	int GetId();

	std::string GetLogin();

	int IsEmptyActual();

	bool IsRightPin(int pin);

	void Erase();

};