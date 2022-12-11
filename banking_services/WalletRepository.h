#pragma once
#include "IRepository.h"
#include "Wallet.h"
#include <vector>
class WalletRepository : public IRepository<Wallet>
{
private:
	static WalletRepository* obj;

	WalletRepository();

protected:
	void Build() override;

public:
	void UpdateDate() override;

	static WalletRepository* GetInstance();

	int GetId();

	std::vector<Wallet> GetRepository();
	
	void Add(Wallet* nwWallet);

	Wallet* GetWallet(int _userId);
};