#include "User.h"



User::User(string Name, uint64_t Money)
{
	this->Name = Name;
	this->Money = Money;
}


uint64_t User::GetMoney() {
	return this->Money;
}

string User::GetName() {
	return this->Name;
}

void User::SetMoney(uint64_t Money) {
	this->Money = Money;
}