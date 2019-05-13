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

	vector<string> DeletedCompanies;

	uint16_t Difficulty;


	TreeItem* GiveObjectOrNull(string Name, TreeItem* Root);

	void Fill();
	void Insert(string Name);
	void InsertTo(string Name, string Where);
	void Print(TreeItem* Root);
	void ChangeMonth(TreeItem* Root);
	void Delete(bool UnderNotExist, TreeItem* Root);
	

public:
	Tree(string Name, uint16_t Difficulty);
	virtual ~Tree();


	bool DoesExist(string Name);
	bool NothingExist();
	bool AvaibleStocks(string Name, uint64_t Stocks);
	
	void NoMoreExist(string Name);
	void BuyStocks(string Name, uint64_t Stocks);
	void ReturnStocks(string, uint64_t Stocks);

	int64_t GetPerStock(string Name);

	vector<string> GetDeletedCompanies();

	//Volají polymorfní funkci z Private
	void Print();
	void ChangeMonth();
	void Delete();
};