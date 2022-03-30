#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/md2.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/filters.h>
using namespace std;
int main()
{
	using CryptoPP::MD2;
	ifstream file("../file.txt");
	string str;
	string TextFromFile{0};
	while (!file.eof()) {
		getline(file, str);
		TextFromFile += str;
	}
	cout << TextFromFile;
	string hesh;
	CryptoPP::Weak1::MD2 hashmd4;
	CryptoPP::StringSource(TextFromFile, true, new CryptoPP::HashFilter(hashmd4,new CryptoPP::HexEncoder(new CryptoPP::StringSink(hesh))));
	cout << endl << hesh << endl;
}
