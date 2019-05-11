#pragma once
#include <string>

using namespace std;

class User
{
private:
	string Name;
	unsigned long long int Money;
public:
	User(string, unsigned long long int);

	unsigned long long int GetMoney();
	string GetName();

	void SetMoney(unsigned long long int);
};

