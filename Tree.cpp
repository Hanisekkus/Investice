#include <iostream>
#include <fstream>
#include "Tree.h"
#define Input "Companies.txt" 

void Tree::Fill() {
	
	string Company = "";
	string Under = "";
	char Letter;
	bool Switch = false;
	
	ifstream Companies;
	Companies.open(Input);

	if (!Companies) {
		cerr << "Unable to open file with Companies!" << endl;
		return;
	}

	while (Companies >> Letter) {
		switch (Letter) {
		case ';': 
		{
			(!Switch && !DoesExist(Company)) ? Insert(Company) : (void)InsertTo(Under, Company);
			Company = "";
			Under = "";
			Switch = false;
			break;
		}
		case ':': 
		{
			(!Switch && !DoesExist(Company)) ? Insert(Company) : (void)InsertTo(Under, Company);
			Under = "";
			Switch = true;
			break;
		}
		default:
			(Switch) ? Under += Letter : Company += Letter;
		}
	}
}

Tree::Tree(string Name, int Difficulty)
{
	this->Difficulty = Difficulty;

	switch (this->Difficulty)
	{
	case 1:	this->Root = new TreeItemGreat(Name); break;
	case 2: this->Root = new TreeItemNormal(Name); break;
	case 3: this->Root = new TreeItemBad(Name); break;
	}

	Fill();
}


Tree::~Tree()
{
	delete[] Root;
}


TreeItem::TreeItem(string Name) {
	this->Name = Name;
	this->Exist = true;
	this->Stocks = rand() % 10000 + 1000;
	this->PerStock = rand() % 100 + 1;
}

void TreeItemBad::ChangeMonth() {
	this->PerStock = this->PerStock + rand() % 50 - (25 + this->Change);
}

void TreeItemNormal::ChangeMonth() {
	this->PerStock = this->PerStock + rand() % 50 - (15 + this->Change);
}

void TreeItemGreat::ChangeMonth() {
	this->PerStock = this->PerStock + rand() % (50 + this->Change) - 5;
}



void Tree::Insert(string Name){
	if (Name == "")return;

	switch (this->Difficulty)
	{
	case 1:	this->Root->Leaves.push_back(new TreeItemGreat(Name)); break;
	case 2: this->Root->Leaves.push_back(new TreeItemNormal(Name)); break;
	case 3: this->Root->Leaves.push_back(new TreeItemBad(Name)); break;
	}
	
}

bool Tree::InsertTo(string Name, string Where) {
	if (Name == "")return false;
	return InsertTo(Name, Where, this->Root);
}

bool Tree::InsertTo(string Name, string Where, TreeItem* root) {
	if (root->Name == Where && root->Exist) {

		switch (this->Difficulty)
		{
		case 1:	root->Leaves.push_back(new TreeItemGreat(Name)); break;
		case 2: root->Leaves.push_back(new TreeItemNormal(Name)); break;
		case 3: root->Leaves.push_back(new TreeItemBad(Name)); break;
		}

		return true;
	}

	if (root->Leaves.empty()) {
		return false;
	}

	for (auto &company : root->Leaves) {
		if (InsertTo(Name, Where, &*company)) {
			return true;
		}
	}
	return false;
}


void Tree::Print() {
	Print(this->Root);
}

void Tree::Print(TreeItem* root) {

	if (root->Leaves.empty() || !root->Exist) {
		return;
	}

	if (LeavesExist(root)) {

		cout << "\t\t";

		(root == this->Root)
			? cout << "Hlavní spoleènosti" << endl << "\t\t\t"
			: cout << root->Name << " owns:" << endl << "\t\t\t";
	}


	int Index = 0;

	for (auto const &company : root->Leaves) {
		if (company->Exist) {
			if (Index)
				cout << ", " << company->Name;
			else
				cout << company->Name;
			cout << " (A: " << company->Stocks << ", C: " << company->PerStock << "Kè)";
			Index++;
		}
	}
	
	cout << endl;

	for (auto &company : root->Leaves) {
		Print(company);
	}
}

bool Tree::LeavesExist(const TreeItem* root) {
	for (auto const &UnderCompany : root->Leaves) {
		if (UnderCompany->Exist)
		{
			return true;
		}
	}
	return false;
}


bool Tree::DoesExist(string Name){
	return DoesExist(Name, this->Root);
}

bool Tree::DoesExist(string Name, TreeItem* root) {
	if (root->Name == Name && root->Exist) {
		return true;
	}

	if (root->Leaves.empty()) {
		return false;
	}

	for (auto &company : root->Leaves) {
		if (DoesExist(Name,company)) {
			return true;
		}
	}
	return false;
}


void Tree::NoMoreExist(string Name) {
	NoMoreExist(Name, this->Root);
}

void Tree::NoMoreExist(string Name, TreeItem* root) {
	if (root->Name == Name) {
		root->Exist = false;
		return;
	}

	if (root->Leaves.empty()) {
		return;
	}

	for (auto &company : root->Leaves) {
		NoMoreExist(Name, company);
	}
}


bool Tree::AvaibleStocks(string Name, unsigned long long int Stocks) {
	return AvaibleStocks(Name, Stocks, this->Root);
}

bool Tree::AvaibleStocks(string Name, unsigned long long int Stocks,TreeItem* root) {
	if (root->Name == Name && root->Exist && root->Stocks >= Stocks) {
		return true;
	}

	if (root->Leaves.empty()) {
		return false;
	}

	for (auto &company : root->Leaves) {
		if (AvaibleStocks(Name, Stocks, company)) {
			return true;
		}
	}
	return false;
}


void Tree::BuyStocks(string Name, unsigned long long int Stocks) {
	BuyStocks(Name, Stocks, this->Root);
}

void Tree::BuyStocks(string Name, unsigned long long int Stocks, TreeItem* root) {
	if (root->Name == Name && root->Exist) {
		root->Stocks -= Stocks;
		return;
	}

	if (root->Leaves.empty()) {
		return;
	}

	for (auto &company : root->Leaves) {
		BuyStocks(Name, Stocks, company);
	}
}


void Tree::ReturnStocks(string Name, unsigned long long int Stocks) {
	ReturnStocks(Name, Stocks, this->Root);
}

void Tree::ReturnStocks(string Name, unsigned long long int Stocks, TreeItem* root) {
	if (root->Name == Name && root->Exist) {
		root->Stocks += Stocks;
		return;
	}

	if (root->Leaves.empty()) {
		return;
	}

	for (auto &company : root->Leaves) {
		ReturnStocks(Name, Stocks, company);
	}
}

void Tree::ChangeMonth() {
	ChangeMonth(this->Root);
}

void Tree::ChangeMonth(TreeItem* &root) {
	if (root->Exist && root != this->Root) {
		root->ChangeMonth();
	}

	if (root->Leaves.empty()) {
		return;
	}

	for (auto &company : root->Leaves) {
		ChangeMonth(company);
	}
}

vector<string> Tree::Delete() {
	vector<string>Deleted;
	Delete(Deleted, this->Root);
	return Deleted;
}

void Tree::Delete(vector<string>&Deleted,TreeItem*& root) {
	if (root->PerStock<=0) {
		root->Exist = false;
		Deleted.push_back(root->Name);
		return;
	}

	if (root->Leaves.empty()) {
		return;
	}

	for (auto &company : root->Leaves) {
		Delete(Deleted,company);
	}
	return;
}



long long int Tree::GetPerStock(string Name) {
	return GetPerStock(Name, this->Root);
}

long long int Tree::GetPerStock(string Name, TreeItem* root) {
	if (root->Name == Name && root->Exist) {
		return root->PerStock;
	}

	if (root->Leaves.empty()) {
		return 0;
	}

	for (auto &company : root->Leaves) {
		long long int PerStock = GetPerStock(Name, company);
		if (PerStock)
			return PerStock;
	}
	return 0;
}

void Tree::SetPerStock(string Name, long long int PerStock) {
	return SetPerStock(Name, PerStock, this->Root);
}

void Tree::SetPerStock(string Name, long long int PerStock, TreeItem* root) {
	if (root->Name == Name && root->Exist) {
		root->PerStock = PerStock;
		return;
	}

	if (root->Leaves.empty()) {
		return;
	}

	for (auto &company : root->Leaves) {
		SetPerStock(Name, PerStock, company);
	}
	return;
}

bool Tree::NothingExist() {
	if (this->Root->Leaves.empty()) {
		return true;
	}

	for (auto const &company : this->Root->Leaves) {
		if (company->Exist) {
			return false;
		}
	}

	return true;
}
