#pragma once
#include <vector>
#include <string>
#include "IRepository.h"
#include "Credit.h"


class CreditRepository : public IRepository<Debt::Credit>
{
private:
	static CreditRepository* obj;

	CreditRepository();

protected:
	void Build() override;

public:
	void Add(Debt::Credit* nwCredit);

	static CreditRepository* GetInstance();

	int GetId();

	void virtual UpdateDate() override;

	std::vector<Debt::Credit> GetRepository();

	void CloseCredit(int _id);
};