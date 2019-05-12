#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TreeItem {
public:
	bool Exist;

	string Name;

	uint64_t Stocks;

	int64_t PerStock;

	vector<TreeItem*> Leaves;


	TreeItem(string Name);


	void virtual ChangeMonth() = 0;
};


class TreeItemBad: public TreeItem {
public:
	int16_t Change = 20;


	TreeItemBad(string Name) :TreeItem(Name) {};


	void ChangeMonth();
};


class TreeItemNormal: public TreeItem {
public:
	int16_t Change = 0;

	TreeItemNormal(string Name) :TreeItem(Name) {};

	void ChangeMonth();
};


class TreeItemGreat : public TreeItem {
public:
	int16_t Change = 20;

	TreeItemGreat(string Name) :TreeItem(Name) {};

	void ChangeMonth();
};


class Tree
{
private:
	TreeItem* Root;

	uint16_t Difficulty;


	void Fill();

	TreeItem* GiveObjectOrNull(string Name, TreeItem* Root);
	
	void Insert(string Name);
	void InsertTo(string Name, string Where);
	void Print(TreeItem* Root);
	void ChangeMonth(TreeItem*&);


	
	void Delete(vector<string>&, TreeItem*&);
	void DeleteUnder(TreeItem*&);


	long long int GetPerStock(string, TreeItem*);
	void SetPerStock(string, long long int, TreeItem*);

	

public:
	Tree(string Name, uint16_t Difficulty);
	virtual ~Tree();


	bool DoesExist(string Name);
	bool AvaibleStocks(string Name, uint64_t Stocks);
	
	void NoMoreExist(string Name);
	void BuyStocks(string Name, uint64_t Stocks);
	void ReturnStocks(string, uint64_t Stocks);
	

	//Volají funkci z Private
	void Print();
	void ChangeMonth();
	
	vector<string> Delete();

	long long int GetPerStock(string);
	void SetPerStock(string,long long int);
	bool NothingExist();
};

