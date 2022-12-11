#pragma once
#include <vector>
#include <string>
#include "IRepository.h"
#include "DebitType.h"

class DebitTypeRepository : public IRepository<DebitType>
{
private:
	static DebitTypeRepository* obj;

	DebitTypeRepository();

protected:
	void Build() override;

public:

	static DebitTypeRepository* GetInstance();

	void virtual UpdateDate() override;

	std::vector<DebitType> GetRepository();

	DebitType GetType(int _id);

};
