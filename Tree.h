#pragma once
#include <string>
#include <vector>

using namespace std;

class TreeItem {
public:
	string Name;
	bool Exist;

	unsigned long long int Stocks;
	long long int PerStock;
	vector<TreeItem*> Leaves;

	TreeItem(string);

	void virtual ChangeMonth() = 0;
};

class TreeItemBad: public TreeItem {
public:
	int Change = 20;

	TreeItemBad(string Name) :TreeItem(Name) {};

	void ChangeMonth();
};

class TreeItemNormal: public TreeItem {
public:
	int Change = 0;

	TreeItemNormal(string Name) :TreeItem(Name) {};

	void ChangeMonth();
};

class TreeItemGreat : public TreeItem {
public:
	int Change = 20;

	TreeItemGreat(string Name) :TreeItem(Name) {};

	void ChangeMonth();
};

class Tree
{
private:
	TreeItem* Root;
	int Difficulty;
	
	bool InsertTo(string, string, TreeItem*);
	void Print(TreeItem*);
	bool LeavesExist(const TreeItem*);
	bool DoesExist(string, TreeItem*);
	void NoMoreExist(string, TreeItem*);
	bool AvaibleStocks(string, unsigned long long int, TreeItem*);
	void BuyStocks(string, unsigned long long int, TreeItem*);
	void ReturnStocks(string, unsigned long long int, TreeItem*);
	void ChangeMonth(TreeItem*&);
	void Delete(vector<string>&, TreeItem*&);
	

	long long int GetPerStock(string, TreeItem*);
	void SetPerStock(string, long long int, TreeItem*);

	void Fill();
public:
	Tree(string,int);
	~Tree();

	void Insert(string);
	bool InsertTo(string, string);
	void Print();
	bool DoesExist(string);
	void NoMoreExist(string);
	bool AvaibleStocks(string, unsigned long long int);
	void BuyStocks(string, unsigned long long int);
	void ReturnStocks(string, unsigned long long int);
	void ChangeMonth();
	vector<string> Delete();

	long long int GetPerStock(string);
	void SetPerStock(string,long long int);
	bool NothingExist();
};

