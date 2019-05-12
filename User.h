#pragma once
#include <iostream>
#include <string>

using namespace std;

class User
{
private:
	string Name;
	
	uint64_t Money;

public:
	User(string, uint64_t);


	uint64_t GetMoney();
	
	string GetName();

	void SetMoney(uint64_t);
};

