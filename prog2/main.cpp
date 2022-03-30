#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/md5.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/filters.h>
#include "cryptopp/mars.h"
#include "cryptopp/rc6.h"
#include "cryptopp/modes.h"
#include "cryptopp/cbcmac.h"
#include <locale>
using namespace std;
void encrypt_MARS() {
    setlocale(LC_ALL, "Russia");
    ifstream ifile;
	string plaintext{0};
    string input_file;
	
    cout << "Введите имя файла для чтения" << endl;
    cin >> input_file;
    ifile.open(input_file);
    char ch;
    while (ifile.get(ch))
        plaintext.push_back(ch);

    byte key[CryptoPP::MARS::DEFAULT_KEYLENGTH], iv[CryptoPP::MARS::BLOCKSIZE];
    memset(key, 0x00, CryptoPP::MARS::DEFAULT_KEYLENGTH);
    memset(iv, 0x00, CryptoPP::MARS::BLOCKSIZE);
    
    string ciphertext;
    cout << "Plain Text (" << plaintext.size() << " bytes)" << std::endl;
    cout << plaintext << endl;
    CryptoPP::MARS::Encryption aesEncryption(key, CryptoPP::MARS::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);
    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(ciphertext));
    stfEncryptor.Put(reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.length());
    stfEncryptor.MessageEnd();	
    cout << "Cipher Text (" << ciphertext.size() << " bytes)" << endl;
    for (int i = 0; i < ciphertext.size(); i++)
        cout << std::hex << (0xFF & static_cast<byte>(ciphertext[i]));
	
    cout << endl << "Введите имя новго файла для записи зашифрованного текста" << endl;
    string file_output;
    cin >> file_output;
	ofstream ofile;
    ofile.open(file_output);
    for (int i = 0; i < ciphertext.size(); i++) {
        ofile << ciphertext[i];
    }
}
void encrypt_RC6() {
    setlocale(LC_ALL, "Russia");	
	ifstream ifile;
	string plaintext{0};
    string input_file;
	
    cout << "Введите имя файла для чтения" << endl;
    cin >> input_file;
    ifile.open(input_file);
    char ch;
    while (ifile.get(ch))
        plaintext.push_back(ch);
	
    byte key[CryptoPP::RC6::DEFAULT_KEYLENGTH], iv[CryptoPP::RC6::BLOCKSIZE];
    memset(key, 0x00, CryptoPP::RC6::DEFAULT_KEYLENGTH);
    memset(iv, 0x00, CryptoPP::RC6::BLOCKSIZE);
	
    string ciphertext;
    cout << "Plain Text (" << plaintext.size() << " bytes)" << std::endl;
    cout << plaintext << endl;
    CryptoPP::RC6::Encryption aesEncryption(key, CryptoPP::RC6::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);
    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(ciphertext));
    stfEncryptor.Put(reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.length());
    stfEncryptor.MessageEnd();
    cout << "Cipher Text (" << ciphertext.size() << " bytes)" << endl;
    for (int i = 0; i < ciphertext.size(); i++)
        cout << std::hex << (0xFF & static_cast<byte>(ciphertext[i]));
	
	cout << endl << "Введите имя новго файла для записи зашифрованного текста" << endl;
    string file_output;
    cin >> file_output;
	ofstream ofile;
    ofile.open(file_output);
    for (int i = 0; i < ciphertext.size(); i++) {
        ofile << ciphertext[i];
    }
}
void decrypt_MARS() {
    setlocale(LC_ALL, "Russia");
    ifstream ifile;
    string plaintext{};
    string file_input;
    cout << "Введите имя файла для чтения" << endl;
    cin >> file_input;
    ifile.open(file_input);
    char ch;
    while (ifile.get(ch))
        plaintext.push_back(ch);

	byte key[CryptoPP::MARS::DEFAULT_KEYLENGTH], iv[CryptoPP::MARS::BLOCKSIZE];
    memset(key, 0x00, CryptoPP::MARS::DEFAULT_KEYLENGTH);
    memset(iv, 0x00, CryptoPP::MARS::BLOCKSIZE);

	string file_output;
    cout << "Введите имя новго файла для записи зашифрованного текста" << endl;
    cin >> file_output;
	ofstream ofile;
    ofile.open(file_output);
	
    string decryptedtext;
    CryptoPP::MARS::Decryption aesDecryption(key, CryptoPP::MARS::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);
    CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedtext));
    stfDecryptor.Put(reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.size());
    stfDecryptor.MessageEnd();
	cout << "Расшифрованный текст:" << endl;
    cout << decryptedtext << endl;
    ofile << decryptedtext;
}
void decrypt_RC6() {
    setlocale(LC_ALL, "Russia");
    ifstream ifile;
    string plaintext{};
    string file_input;
    cout << "Введите имя файла для чтения" << endl;
    cin >> file_input;
    ifile.open(file_input);
    char ch;
    while (ifile.get(ch))
        plaintext.push_back(ch);
		
    byte key[CryptoPP::RC6::DEFAULT_KEYLENGTH], iv[CryptoPP::RC6::BLOCKSIZE];
    memset(key, 0x00, CryptoPP::RC6::DEFAULT_KEYLENGTH);
    memset(iv, 0x00, CryptoPP::RC6::BLOCKSIZE);
	
	string file_output;
    cout << "Введите имя новго файла для записи зашифрованного текста";
    cin >> file_output;
	ofstream ofile;
    ofile.open(file_output);
	
    string decryptedtext;
    CryptoPP::RC6::Decryption aesDecryption(key, CryptoPP::RC6::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);
    CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedtext));
    stfDecryptor.Put(reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.size());
    stfDecryptor.MessageEnd();
	cout << "Введите имя файла для чтения" << endl;
    cout << decryptedtext << endl;
    ofile << decryptedtext;
}
int main()
{
    setlocale(LC_ALL, "Russia");
    string mode;
    int choice;
	int reload = 1;
	
	do{
		cout << "Выберете режим MARS или RC6" << endl;
		cin >> mode;
		if (mode == "MARS"){
			cout << "Ведите 1, чтобы зашифровать, 2 дешифровать" << endl;
			cin >> choice;
			if (choice == 1)
				encrypt_MARS();
			else  if (choice == 2)
				decrypt_MARS();
			cout << "Введите 1 чтобы повторить выбор, 0 выйти" << endl;
			cin >> reload;
		}else if (mode == "RC6"){
			cout << "Ведите 1, чтобы зашифровать, 2 дешифровать" << endl;
			cin >> choice;
			if (choice == 1)
				encrypt_RC6();
			else  if (choice == 2)
				decrypt_RC6();
			cout << "Введите 1 чтобы повторить выбор, 0 выйти" << endl;
			cin >> reload;
		}
	}while(reload == 1);

	
    return 0;
}