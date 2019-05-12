#include "Tree.h"

//Tree.h knihovny
//#include <iostream>
//#include <string>
//#include <vector>
#include <fstream>

#define Input "Companies.txt" 


//Konstruktor t��dy Tree
Tree::Tree(string Name, uint16_t Difficulty)
{
	this->Difficulty = Difficulty;

	switch (this->Difficulty)
	{
	case 1:	this->Root = new TreeItemGreat(Name); break;
	case 2: this->Root = new TreeItemNormal(Name); break;
	case 3: this->Root = new TreeItemBad(Name); break;
	}

	this->Fill();
}

//Destruktor t��dy Tree
Tree::~Tree()
{
	delete Root;
}

//Konstruktor t��dy TreeItem
//	Abstraktn� t��da (pouze pro d�di�e)
TreeItem::TreeItem(string Name)
{
	this->Name = Name;
	this->Exist = true;
	this->Stocks = rand() % 10000 + 1000;
	this->PerStock = rand() % 100 + 1;
}

//Metoda pro nejt잚� obt�nosti
void TreeItemBad::ChangeMonth()
{
	this->PerStock = this->PerStock + rand() % 50 - (25 + this->Change);
}

//Metoda pro norm�ln� obt�nosti
void TreeItemNormal::ChangeMonth()
{
	this->PerStock = this->PerStock + rand() % 50 - (15 + this->Change);
}

//Metoda pro nejleh�� obt�nost
void TreeItemGreat::ChangeMonth()
{
	this->PerStock = this->PerStock + rand() % (50 + this->Change) - 5;
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
		DeleteUnder(root);
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

void Tree::DeleteUnder(TreeItem*& root) {
	if (root == nullptr) {
		return;
	}

	root->Exist = false;

	if (root->Leaves.empty()) {
		return;
	}

	for (auto &Under : root->Leaves) {
		DeleteUnder(Under);
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



//
// Private
//



//Metoda t��da Tree
//	Napln� strom ko�eny a list�m
//	Prob�hne pouze JEDNOU!
void Tree::Fill()
{
	string Company;
	string Under;

	char Letter;

	bool Switch = true;

	ifstream Companies;
	Companies.open(Input);


	if (!Companies)
	{
		cerr << "Unable to open file with Companies!" << endl;
		return;
	}

	while (Companies >> Letter)
	{
		switch (Letter)
		{
		case ';':
		{
			if (!(Switch && DoesExist(Company)))
			{
				(Switch) ? Insert(Company) : InsertTo(Under, Company);
			}

			Company = "";
			Under = "";
			Switch = true;

			break;
		}
		case ':':
		{
			if (!(Switch && DoesExist(Company)))
			{
				(Switch) ? Insert(Company) : InsertTo(Under, Company);
			}			

			Under = "";
			Switch = false;

			break;
		}
		default:
			(Switch) ? Company += Letter : Under += Letter;
		}
	}

	Companies.close();
}


//Rekurzivn� metoda t��dy Tree
//	Vyhled� po�adovan� objekt
//		Vr�t� objekt pokud existuje
//		Vr�t� nullptr pokud neexistuje
TreeItem* Tree::GiveObjectOrNull(string Name, TreeItem* Root)
{
	if (Root == nullptr)
	{
		return nullptr;
	}

	if (Root->Name == Name)
	{
		return Root;
	}


	for (auto const &Company : Root->Leaves)
	{
		if (GiveObjectOrNull(Name, Company) != nullptr)
		{
			return GiveObjectOrNull(Name, Company);
		}
	}

	return nullptr;
}


//Metoda t��dy Tree
//	Do ko�ene vlo�� nov� objekt
void Tree::Insert(string Name)
{
	switch (this->Difficulty)
	{
	case 1:	this->Root->Leaves.push_back(new TreeItemGreat(Name)); break;
	case 2: this->Root->Leaves.push_back(new TreeItemNormal(Name)); break;
	case 3: this->Root->Leaves.push_back(new TreeItemBad(Name)); break;
	}
}


//Metoda t��dy Tree
//	Do hledan�ho objektu vytvo�� nov� objekt
void Tree::InsertTo(string Name, string Where)
{
	TreeItem* root = GiveObjectOrNull(Where, this->Root);

	if (root == nullptr)
	{
		return;
	}

	switch (this->Difficulty)
	{
	case 1:	root->Leaves.push_back(new TreeItemGreat(Name)); break;
	case 2: root->Leaves.push_back(new TreeItemNormal(Name)); break;
	case 3: root->Leaves.push_back(new TreeItemBad(Name)); break;
	}


	root = nullptr;
}


//PUBLIC
//Metoda t��dy Tree
//	Zavol� priv�tn� metodu kter� vyp�e cel� strom
void Tree::Print()
{
	Print(this->Root);
}

//Metoda t��dy Tree
//	Vyp�e data ze stromu podle struktury
void Tree::Print(TreeItem* Root)
{
	uint16_t Index = 0;


	if (Root->Leaves.empty() || !Root->Exist)
	{
		return;
	}

	for (auto const &UnderCompany : Root->Leaves)
	{
		if(UnderCompany->Exist)
		{
			(Root == this->Root)
				? cout << endl << "\t\t" << "Hlavn� spole�nosti" << endl << "\t\t\t"
				: cout << endl << "\t\t" << Root->Name << " vlastn�:" << endl << "\t\t\t";

			break;
		}
	}

	for (auto const &company : Root->Leaves)
	{
		if (company->Exist)
		{
			if (Index)
			{
				cout << ", " << company->Name;
			}
				
			else
			{
				cout << company->Name;
			}
				
			cout << " (A: " << company->Stocks << ", C: " << company->PerStock << "K�)";
			Index++;
		}
	}

	for (auto const &company : Root->Leaves) {
		Print(company);
	}
}


//PUBLIC
//Metoda t��dy Tree
//	Zavol� priv�tn� metodu kter� zm�n� hodnoty ve strom�
void Tree::ChangeMonth()
{
	ChangeMonth(this->Root);
}

//Metoda t��dy Tree
//	M�n� poka�d�m zavol�n� hodnoty ve strom�
void Tree::ChangeMonth(TreeItem* &root)
{
	if (root->Exist && root != this->Root)
	{
		root->ChangeMonth();
	}

	if (root->Leaves.empty())
	{
		return;
	}

	for (auto &company : root->Leaves)
	{
		ChangeMonth(company);
	}
}



//
// Public
//



//Metoda t��dy Tree
//	Vrac� True pokud objekt existuje
//	Vrac� False pokud objekt neexistuje
bool Tree::DoesExist(string Name)
{
	TreeItem* root = GiveObjectOrNull(Name, this->Root);

	if (root == nullptr)
	{
		return false;
	}

	bool DoesExist = root->Exist;


	root = nullptr;


	if (DoesExist)
	{
		return true;
	}

	return false;
}


//Metoda t��dy Tree
//	Zjist� zda objekt m� dost akci� na prod�n�
bool Tree::AvaibleStocks(string Name, uint64_t Stocks)
{
	bool GoodEnough;


	TreeItem* root = GiveObjectOrNull(Name, this->Root);

	if (root == nullptr)
	{
		return false;
	}

	(root->Stocks >= Stocks && root->Exist) ? GoodEnough = true : GoodEnough = false;


	root = nullptr;


	return GoodEnough;
}


//Metoda t��dy Tree
//	P�enastav� hodnotu objektu Exist na false
void Tree::NoMoreExist(string Name)
{
	TreeItem* root = GiveObjectOrNull(Name, this->Root);

	if (root == nullptr)
	{
		return;
	}

	if (root->Exist)
	{
		root->Exist = false;
	}


	root = nullptr;
}


//Metoda t��dy Tree
//	P�enastav� hodnotu objektu Stocks o parametr
void Tree::BuyStocks(string Name, uint64_t Stocks)
{
	TreeItem* root = GiveObjectOrNull(Name, this->Root);

	if (root == nullptr)
	{
		return;
	}

	if (root->Stocks >= Stocks && root->Exist)
	{
		root->Stocks -= Stocks;
	}


	root = nullptr;
}


//Metoda t��dy Tree
//	P�enastav� hodnotu objektu Stocks o parametr
void Tree::ReturnStocks(string Name, uint64_t Stocks)
{
	TreeItem* root = GiveObjectOrNull(Name, this->Root);

	if (root == nullptr)
	{
		return;
	}

	if (root->Exist)
	{
		root->Stocks += Stocks;
	}


	root = nullptr;
}

