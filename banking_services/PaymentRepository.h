#pragma once
#include <vector>
#include "IRepository.h"
#include "Payment.h"

class PaymentRepository : public IRepository<Payment>
{
private:
	static PaymentRepository* obj;

	PaymentRepository();

protected:
	void Build() override;

public:
	void UpdateDate() override;

	static PaymentRepository* GetInstance();

	int GetId();

	std::vector<Payment> GetRepository();

	void Add(Payment* nwPayment);

};