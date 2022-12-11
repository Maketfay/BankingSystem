#pragma once
#include <vector>
#include <string>
#include "IRepository.h"
#include "Debit.h"


class DebitRepository : public IRepository<Debt::Debit>
{
private:
	static DebitRepository* obj;

	DebitRepository();

protected:
	void Build() override;

public:
	void Add(Debt::Debit* nwDebit);

	static DebitRepository* GetInstance();

	int GetId();

	void virtual UpdateDate() override;

	std::vector<Debt::Debit> GetRepository();

	void CloseDebit(int _id);
};