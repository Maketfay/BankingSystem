#include <iostream>
#include "Hashing.h"

const int PRIME_CONST = 31;

std::string Hashing(std::string key) {
    float hashCode = 0;
    for (int i = 0; i < key.length(); i++) {
        hashCode += key[i] * pow(PRIME_CONST, i/10.);
    }

    std::string hash = std::to_string((long long)(hashCode*1000000));
    return hash;
}