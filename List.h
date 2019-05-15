#pragma once
#include <string>
#include <vector>
#include "tree.h"

using namespace std;



class ListItem {
public:
	string Name;

	uint64_t Stocks;
	uint64_t Months;

	int64_t PerOneStock;

	ListItem* Next;
	ListItem* Previous;


	ListItem(string Name, uint64_t Stocks, Tree* Item);
};


class List
{
private:
	ListItem* Head;
	ListItem* Tail;

	uint64_t Count;


	void Insert(string Name, uint64_t Stocks, ListItem* item, Tree* tree);
	void Print(ListItem* list, uint16_t Index);
	void ChangePerMonth(ListItem* list, Tree* tree);
	void RemoveByName(string Name);

	vector<string> Delete(vector<string> Deleted, ListItem* item);

	ListItem* GiveObjectOrNull(string Name, ListItem* Root);

public:
	List();
	~List();

	uint64_t GetCount();
	uint64_t GetStocks(string Name);
	uint64_t GetDuration(string Name);
	uint64_t Remove(string Name, uint64_t Stocks);

	void Insert(string Name, uint64_t Stocks, Tree* tree);
	void InsertTo(string Name, uint64_t Stocks);

	void Print();
	void ChangePerMonth(Tree* tree);
	bool DoesExist(string Name);

	vector<string> Delete();
};