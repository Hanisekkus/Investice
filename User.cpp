#include "User.h"



User::User(string Name, unsigned long long int Money)
{
	this->Name = Name;
	this->Money = Money;
}

unsigned long long int User::GetMoney() {
	return this->Money;
}

string User::GetName() {
	return this->Name;
}

void User::SetMoney(unsigned long long int Money) {
	this->Money = Money;
}