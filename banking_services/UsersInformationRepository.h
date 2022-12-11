#pragma once
#include "IRepository.h"
#include "UsersInformation.h"

class UsersInformationRepository : public IRepository<UsersInformation>
{
private:

	static UsersInformationRepository* obj;

	UsersInformationRepository();

protected:

	void Build() override;

public:

	void UpdateDate() override;

	static UsersInformationRepository* GetInstance();

	int GetCommonId();

	void AddInformation(UsersInformation* nwUsersInformation);

	std::vector<UsersInformation> GetRepository();

	void Edit(int id, std::string name, std::string surname, std::string patronymic, std::string phoneNumber);

};