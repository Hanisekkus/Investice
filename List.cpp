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
	delete this->Head;
	delete this->Tail;
}


ListItem::ListItem(string Name,uint64_t Stocks, Tree* item)
{
	this->Name = Name;
	this->Stocks = Stocks;
	this->PerOneStock = item->GetPerStock(this->Name);
	this->Next = nullptr;
	this->Previous = nullptr;
	this->Months = 0;
}



uint64_t List::GetCount()
{
	return this->Count;
}


uint64_t List::GetStocks(string Name)
{
	ListItem* item = GiveObjectOrNull(Name, this->Head);

	uint64_t Stocks;


	if (item == nullptr)
	{
		return 0;
	}

	Stocks = item->Stocks;


	item = nullptr;


	return Stocks;
}


void List::Insert(string Name, uint64_t Stocks, Tree* tree)
{
	this->Count++;
	Insert(Name, Stocks, this->Head, tree);
}


void List::Insert(string Name, uint64_t Stocks,ListItem* item, Tree* tree)
{
	if (this->Head == nullptr)
	{
		this->Head = new ListItem(Name, Stocks, tree);
		this->Tail = this->Head;

		return;
	}


	if (item->Next == nullptr)
	{
		item->Next = new ListItem(Name, Stocks, tree);
		item->Next->Previous = item;
		this->Tail = item->Next;

		return;
	}

	Insert(Name, Stocks, item->Next, tree);
}


void List::InsertTo(string Name, uint64_t Stocks)
{
	ListItem* item = GiveObjectOrNull(Name, this->Head);


	if (item == nullptr)
	{
		return ;
	}

	item->Stocks += Stocks;


	item = nullptr;


	return;
}

uint64_t List::Remove(string Name, uint64_t Stocks)
{
	ListItem* item = GiveObjectOrNull(Name, this->Head);

	uint64_t ItemStocks = item->Stocks;
	uint64_t ItemPerStock = item->PerOneStock;


	if (item == nullptr)
	{
		return 0;
	}


	if (ItemStocks <= Stocks)
	{
		uint64_t Money = ItemStocks * ItemPerStock;

		if (this->Head == item)
			this->Head = item->Next;

		if (this->Tail == item)
			this->Tail = item->Previous;

		if (item->Next != nullptr)
			item->Next->Previous = item->Previous;

		if (item->Previous != nullptr)
			item->Previous->Next = item->Next;

		delete item;
		item = nullptr;

		return Money;
	}

	item->Stocks -= Stocks;


	item = nullptr;


	return ItemPerStock * Stocks;
}


void List::Print()
{
	cout << endl << "\t\t";

	Print(this->Head, 0);

	cout << endl;
}


void List::Print(ListItem* list, uint16_t Index)
{
	if (list == nullptr)
	{
		return;
	}


	if (Index == 3)
	{
		cout <<endl << "\t\t";
		Index = 0;
	}

	cout << list->Name << " : " << list->Stocks * list->PerOneStock
		<< "Kè (A: " << list->Stocks << ", M: " << list->Months << ")" << "    ";
	
	Print(list->Next, Index += 1);
}


void List::ChangePerMonth(Tree* tree)
{
	ChangePerMonth(this->Head,tree);
}


void List::ChangePerMonth(ListItem* item,Tree* tree)
{
	if (item == nullptr)
	{
		return;
	}

	item->Months++;
	item->PerOneStock = tree->GetPerStock(item->Name);

	ChangePerMonth(item->Next, tree);


	if (item->PerOneStock <= 0)
	{
		Remove(item->Name, item->Stocks);
	}
}


bool List::DoesExist(string Name)
{
	ListItem* item = GiveObjectOrNull(Name, this->Head);


	if (item == nullptr)
	{
		return false;
	}


	item = nullptr;


	return true;
}


uint64_t List::GetDuration(string Name)
{
	ListItem* item = GiveObjectOrNull(Name, this->Head);

	uint64_t Months;


	if (item == nullptr)
	{
		return 0;
	}

	Months = item->Months;


	item = nullptr;


	return Months;
}


vector<string> List::Delete()
{
	vector<string> Deleted = Delete(Deleted, this->Head);

	for (auto item : Deleted)
	{
		RemoveByName(item);
	}

	return Deleted;
}


vector<string> List::Delete(vector<string>Deleted, ListItem* item)
{
	if (item == nullptr)
		return Deleted;

	if (item->PerOneStock <= 0) {
		Deleted.push_back(item->Name);
	}

	return Delete(Deleted, item->Next);
}



ListItem* List::GiveObjectOrNull(string Name, ListItem* item)
{
	if (item == nullptr)
		return nullptr;

	if (item->Name == Name) {
		return item;
	}

	return GiveObjectOrNull(Name, item->Next);
}


void List::RemoveByName(string Name)
{
	ListItem* item = GiveObjectOrNull(Name, this->Head);

	if (item == nullptr)
	{
		return;
	}

	Remove(item->Name, item->Stocks);


	item = nullptr;
}