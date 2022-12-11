#pragma once
#include <string>
#include <fstream>

class Users
{
public:
	int id;
	std::string name;
	std::string password;

	Users();

	Users(std::string _name);

	Users(int _id, std::string _name);

	Users(int _id, std::string _name, std::string _password);

	Users(std::string _name, std::string _password);

};