#include "GenerateAccountNumber.h"
#define ACCOUNT_NUMBER_COUNT 10
std::string GenerateAccountNumber(int id)
{
    std::string tmp = std::to_string(++id);
    std::string result;
    
    result.clear();

    for (int i = 0; i < ACCOUNT_NUMBER_COUNT; i++) { result.push_back('0'); }
    
    int j = 0;
    for (int i = ACCOUNT_NUMBER_COUNT - tmp.size(); i < ACCOUNT_NUMBER_COUNT; i++) { result[i] = tmp[j++]; }

    return result;
}
