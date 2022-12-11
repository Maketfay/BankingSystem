#pragma once
#include <string>
class UsersInformation {
public:

	int id;

	std::string name;

	std::string surname;

	std::string patronymic;

	std::string phoneNumber;

	std::string pasportNumber;

	std::string type;

	UsersInformation();

	UsersInformation(std::string _name, std::string _surname, 
		std::string _patronymic, std::string _phoneNumber, 
		std::string _pasportNumber,std::string _type);

	UsersInformation(int id, std::string _name, std::string _surname,
		std::string _patronymic, std::string _phoneNumber,
		std::string _pasportNumber, std::string _type);

};