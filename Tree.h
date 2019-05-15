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

	vector<string> Companies;


	bool DoesExist(string Name);

	vector<string> GetExistCompanies();
	vector<string> GetNotExistCompanies();

	TreeItem* GiveObjectOrNull(string Name, TreeItem* Root);

	void Fill();
	void Insert(string Name);
	void InsertTo(string Name, string Where);
	void Delete(bool UnderNotExist, TreeItem* Root);

	//Volané z Public
	void Print(TreeItem* Root);
	void ChangeMonth(TreeItem* Root);


public:
	Tree(string Name, uint16_t Difficulty);
	virtual ~Tree();


	uint64_t GetStocks(string Name);

	int64_t GetPerStock(string Name);

	
	void BuyStocks(string Name, uint64_t Stocks);
	void ReturnStocks(string Name, uint64_t Stocks);

	vector<string> GetCompanies(uint16_t Options);


	//Volají polymorfní funkci z Private
	void Print();
	void ChangeMonth();
};