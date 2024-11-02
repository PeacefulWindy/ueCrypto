#pragma once
#include<define.hpp>
#include<string>

void EXPORT rsa_gen(uint32_t keyLen,std::string& publicKey, std::string privateKey);
std::string EXPORT rsa_decode(std::string keyData, std::string input);
std::string EXPORT rsa_encode(std::string keyData, std::string input);