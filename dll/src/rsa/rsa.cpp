#include<rsa/rsa.hpp>
#include<cryptopp/cryptlib.h>
#include<cryptopp/rsa.h>
#include<cryptopp/base64.h>
#include<cryptopp/osrng.h>
#include<cryptopp/files.h>

void rsa_gen(uint32_t keyLen,std::string& publicKeyData, std::string privateKeyData)
{
	auto rng = CryptoPP::AutoSeededRandomPool();
	auto privateKey = CryptoPP::InvertibleRSAFunction();
	privateKey.Initialize(rng, keyLen);

	auto privateKeySink = CryptoPP::Base64Encoder(new CryptoPP::StringSink(privateKeyData));
	privateKey.DEREncode(privateKeySink);
	privateKeySink.MessageEnd();

	auto publicKey = CryptoPP::RSAFunction(privateKey);
	auto pulbicKeySink = CryptoPP::Base64Encoder(new CryptoPP::StringSink(publicKeyData));
	publicKey.DEREncode(pulbicKeySink);
	pulbicKeySink.MessageEnd();
}

std::string rsa_decode(std::string keyData, std::string input)
{
	auto key = CryptoPP::RSA::PrivateKey();
	auto keySource = CryptoPP::StringSource(keyData, true, new CryptoPP::Base64Decoder);

	try
	{
		key.BERDecode(keySource);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return "";
	}

	auto encryptor = CryptoPP::RSAES_OAEP_SHA_Decryptor(key);
	auto outputText = std::string();
	auto rng = CryptoPP::AutoSeededRandomPool();

	try
	{
		CryptoPP::StringSource((const CryptoPP::byte*)input.c_str(), input.length(), true, new CryptoPP::PK_DecryptorFilter(rng, encryptor, new CryptoPP::StringSink(outputText)));
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return "";
	}

	return outputText;
}

std::string rsa_encode(std::string keyData,std::string input)
{
	auto key = CryptoPP::RSA::PublicKey();
	auto keySource = CryptoPP::StringSource(keyData, true, new CryptoPP::Base64Decoder);

	try
	{
		key.BERDecode(keySource);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return "";
	}

	auto encryptor = CryptoPP::RSAES_OAEP_SHA_Encryptor(key);
	auto rng = CryptoPP::AutoSeededRandomPool();
	auto outputText = std::string();

	try
	{
		CryptoPP::StringSource((const CryptoPP::byte*)input.c_str(), input.length(), true, new CryptoPP::PK_EncryptorFilter(rng, encryptor, new CryptoPP::StringSink(outputText)));
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return "";
	}

	return outputText;
}
