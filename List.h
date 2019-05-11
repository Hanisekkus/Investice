#pragma once
#include <string>
#include <vector>
#include "tree.h"

using namespace std;

class ListItem {
public:
	string Name;
	unsigned long long int Stocks;
	long long int PerOneStock;
	unsigned long long int Months;

	ListItem* Next;
	ListItem* Previous;


	ListItem(string, unsigned long long int, Tree*);
};


class List
{
private:
	ListItem* Head;
	ListItem* Tail;
	unsigned int Count;

	unsigned long long int GetStocks(string, ListItem*);

	unsigned long long int Remove(string, ListItem*);
	unsigned long long int Remove(string, unsigned long long int, ListItem*);
	void Insert(string, unsigned long long int, ListItem*, Tree*);
	void InsertTo(string,unsigned long long int, ListItem*);
	void Print(ListItem*,int);
	void ChangePerMonth(ListItem*&,Tree*);
	bool DoesExist(string, ListItem*);
	unsigned long long int GetDuration(string,const ListItem*);

	vector<string> Delete(vector<string>,ListItem*);
public:
	List();
	~List();

	unsigned int GetCount();
	unsigned long long int GetStocks(string);

	unsigned long long int Remove(string);
	unsigned long long int Remove(string, unsigned long long int);
	void Insert(string, unsigned long long int, Tree*);
	void InsertTo(string, unsigned long long int);
	void Print();
	void ChangePerMonth(Tree*);
	bool DoesExist(string);
	unsigned long long int GetDuration(string);

	vector<string> Delete();
};