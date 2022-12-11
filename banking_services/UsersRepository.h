#pragma once
#include <vector>
#include <string>
#include "IRepository.h"
#include "Users.h"

class Users;

class UsersRepository : public IRepository<Users>
{
private:
	static UsersRepository* obj;

	UsersRepository();

protected:
	void Build() override;

public:
	void AddUser(Users* nwUser);

	static UsersRepository* GetInstance();
	
	int GetId();

	void virtual UpdateDate() override;

	std::vector<Users> GetRepository();

	void ChangePassword(int _userId, std::string newPassword);
};
