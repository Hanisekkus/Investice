#include <iostream>

#include "List.h"

using namespace std;

List::List()
{
	this->Head = nullptr;
	this->Tail = nullptr;
	this->Count = 0;
}


List::~List()
{
	delete[] this->Head;
	delete this->Tail;
}


ListItem::ListItem(string Name,unsigned long long int Stocks, Tree* tree) {
	this->Name = Name;
	this->Stocks = Stocks;
	this->PerOneStock = tree->GetPerStock(this->Name);
	this->Next = nullptr;
	this->Previous = nullptr;
}



unsigned int List::GetCount() {
	return this->Count;
}


unsigned long long int List::GetStocks(string Name) {
	return GetStocks(Name, this->Head);
}

unsigned long long int List::GetStocks(string Name, ListItem* head) {
	if (head == nullptr)return 0;

	if (head->Name == Name) {
		return head->Stocks;
	}
	return GetStocks(Name, head->Next);
}


void List::Insert(string Name, unsigned long long int Stocks, Tree* tree) {
	this->Count++;
	Insert(Name, Stocks, this->Head, tree);
}


void List::Insert(string Name, unsigned long long int Stocks,ListItem* head, Tree* tree) {


	if (this->Head == nullptr) {
		this->Head = new ListItem(Name, Stocks, tree);

		this->Tail = this->Head;

		return;
	}


	if (head->Next == nullptr)
	{
		head->Next = new ListItem(Name, Stocks, tree);
		head->Next->Previous = head;
		this->Tail = head->Next;

		return;
	}

	Insert(Name, Stocks, head->Next, tree);
}

void List::InsertTo(string Name, unsigned long long int Stocks) {
	InsertTo(Name, Stocks, this->Head);
}

void List::InsertTo(string Name, unsigned long long int Stocks, ListItem* head) {
	if (head == nullptr)return;

	if (head->Name == Name) {
		head->Stocks += Stocks;
		return;
	}
	InsertTo(Name, Stocks, head->Next);
}


unsigned long long int List::Remove(string Name) {
	return Remove(Name, this->Head);
}

unsigned long long int List::Remove(string Name, ListItem* head) {
	if (head == nullptr) {
		return 0;
	}

	if (head->Name == Name) {
		unsigned long long int Money = head->Stocks * head->PerOneStock;

		if (this->Head == head)
			this->Head = head->Next;

		if (this->Tail == head)
			this->Tail = head->Previous;

		if (head->Next != nullptr) 
			head->Next->Previous = head->Previous;

		if (head->Previous != nullptr) 
			head->Previous->Next = head->Next;

		delete head;
		return Money;
	}
	return Remove(Name, head->Next);
}

unsigned long long int List::Remove(string Name, unsigned long long int Stocks) {
	return Remove(Name, Stocks, this->Head);
}

unsigned long long int List::Remove(string Name, unsigned long long int Stocks, ListItem* head) {
	if (head == nullptr) {
		return 0;
	}

	if (head->Name == Name) {

		if (head->Stocks <= Stocks) {
			return Remove(Name, head);
		}

		head->Stocks = head->Stocks - Stocks;

		return head->PerOneStock * Stocks;
	}
	return Remove(Name, Stocks, head->Next);
}


void List::Print() {
	cout << "\t\t";
	Print(this->Head,0);
}

void List::Print(ListItem* head, int Index) {
	if (head == nullptr) {
		return;
	}
	if (Index == 3) {
		cout <<endl << "\t\t";
		Index = 0;
	}
	cout << head->Name << " : " << head->Stocks * head->PerOneStock << "Kè (A: " << head->Stocks << ")" << "    ";
	
	Print(head->Next, Index+=1);
}

void List::ChangePerMonth(Tree* tree) {
	ChangePerMonth(this->Head,tree);
}


void List::ChangePerMonth(ListItem* &head,Tree* tree) {
	if (head == nullptr) {
		return;
	}
	head->PerOneStock = tree->GetPerStock(head->Name);
	ChangePerMonth(head->Next, tree);

	if (head->PerOneStock <= 0)
	{
		Remove(head->Name,head);
	}



}

bool List::DoesExist(string Name) {
	return DoesExist(Name, this->Head);
}

bool List::DoesExist(string Name, ListItem* head) {
	if (head == nullptr)return 0;
	if (head->Name == Name)return 1;
	return DoesExist(Name, head->Next);
}



vector<string> List::Delete() {
	vector<string> Deleted = Delete(Deleted, this->Head);

	for (auto head : Deleted) {
		Remove(head);
	}

	return Deleted;
}


vector<string> List::Delete(vector<string>Deleted, ListItem* head) {
	if (head == nullptr)
		return Deleted;

	if (head->PerOneStock <= 0) {
		Deleted.push_back(head->Name);
	}

	return Delete(Deleted, head->Next);
}