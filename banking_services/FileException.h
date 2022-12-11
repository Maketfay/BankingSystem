#pragma once
#include <exception>
#include <string>

class FileException : public std::exception
{
public:
	FileException(const char* msg, std::string value);

	std::string GetValue();

private:
	std::string value;
};