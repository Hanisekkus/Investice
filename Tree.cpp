#include "Tree.h"

//Tree.h knihovny
//#include <iostream>
//#include <string>
//#include <vector>
#include <fstream>

#define Input "Companies.txt" 


//Konstruktor tøídy Tree
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

//Destruktor tøídy Tree
Tree::~Tree()
{
	delete Root;
}


//Konstruktor tøídy TreeItem
//	Abstraktní tøída (pouze pro dìdièe)
TreeItem::TreeItem(string Name)
{
	this->Name = Name;
	this->Exist = true;
	this->Stocks = rand() % 10000 + 1000;
	this->PerStock = rand() % 100 + 1;
}

//Metoda pro nejtìžší obtížnosti
void TreeItemBad::ChangeMonth()
{
	this->PerStock = this->PerStock + rand() % 50 - (25 + this->Change);
}

//Metoda pro normální obtížnosti
void TreeItemNormal::ChangeMonth()
{
	this->PerStock = this->PerStock + rand() % 50 - (15 + this->Change);
}

//Metoda pro nejlehèí obtížnost
void TreeItemGreat::ChangeMonth()
{
	this->PerStock = this->PerStock + rand() % (50 + this->Change) - 5;
}



//
// Private
//



//Metoda tøída Tree
//	Naplní strom koøeny a listím
//	Probìhne pouze JEDNOU!
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


//Rekurzivní metoda tøídy Tree
//	Vyhledá požadovaný objekt
//		Vrátí objekt pokud existuje
//		Vrátí nullptr pokud neexistuje
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


//Metoda tøídy Tree
//	Do koøene vloží nový objekt
void Tree::Insert(string Name)
{
	this->Companies.push_back(Name);


	switch (this->Difficulty)
	{
	case 1:	this->Root->Leaves.push_back(new TreeItemGreat(Name)); break;
	case 2: this->Root->Leaves.push_back(new TreeItemNormal(Name)); break;
	case 3: this->Root->Leaves.push_back(new TreeItemBad(Name)); break;
	}
}


//Metoda tøídy Tree
//	Do hledaného objektu vytvoøí nový objekt
void Tree::InsertTo(string Name, string Where)
{
	TreeItem* root = GiveObjectOrNull(Where, this->Root);

	if (root == nullptr)
	{
		return;
	}


	this->Companies.push_back(Name);


	switch (this->Difficulty)
	{
	case 1:	root->Leaves.push_back(new TreeItemGreat(Name)); break;
	case 2: root->Leaves.push_back(new TreeItemNormal(Name)); break;
	case 3: root->Leaves.push_back(new TreeItemBad(Name)); break;
	}


	root = nullptr;
}


//PUBLIC
//Metoda tøídy Tree
//	Zavolá privátní metodu která vypíše celý strom
void Tree::Print()
{
	Print(this->Root);
}

//Metoda tøídy Tree
//	Vypíše data ze stromu podle struktury
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
				? cout << endl << "\t\t" << "Hlavní spoleènosti" << endl << "\t\t\t"
				: cout << endl << "\t\t" << Root->Name << " vlastní:" << endl << "\t\t\t";

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
				
			cout << " (A: " << company->Stocks << ", C: " << company->PerStock << "Kè)";
			Index++;
		}
	}

	for (auto const &company : Root->Leaves)
	{
		Print(company);
	}
}


//PUBLIC
//Metoda tøídy Tree
//	Zavolá privátní metodu která zmìní hodnoty ve stromì
void Tree::ChangeMonth()
{
	ChangeMonth(this->Root);
	Delete(false, this->Root);
}

//Metoda tøídy Tree
//	Mìní pokaždém zavolání hodnoty ve stromì
void Tree::ChangeMonth(TreeItem* Root)
{
	if (Root->Exist && Root != this->Root)
	{
		Root->ChangeMonth();
	}

	if (Root->Leaves.empty())
	{
		return;
	}

	for (auto &company : Root->Leaves)
	{
		ChangeMonth(company);
	}
}


//Metoda tøídy Tree
//	Mìní pokaždém zavolání hodnoty ve stromì
void Tree::Delete(bool UnderNotExist, TreeItem* Root)
{
	if (Root->PerStock <= 0 || UnderNotExist)
	{
		Root->Exist = false;
		UnderNotExist = true;
	}

	if (Root->Leaves.empty())
	{
		return;
	}

	for (auto &Company : Root->Leaves)
	{
		if(Company->Exist)
		{
			Delete(UnderNotExist, Company);
		}
	}
	return;
}



//
//			 Public
//



//Metoda tøídy Tree
//	Vrací True pokud objekt existuje
//	Vrací False pokud objekt neexistuje
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


//Metoda tøídy Tree
//	Pøenastaví hodnotu objektu Stocks o parametr
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


//Metoda tøídy Tree
//	Pøenastaví hodnotu objektu Stocks o parametr
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


//Metoda tøídy Tree
//	Vrátí cenu za akcii dané spoleènosti
int64_t Tree::GetPerStock(string Name)
{
	TreeItem* Root = GiveObjectOrNull(Name, this->Root);

	int64_t PerStock;


	if (Root == nullptr)
	{
		return 0;
	}

	(Root->Exist) ? PerStock = Root->PerStock : PerStock = 0;


	Root = nullptr;


	return PerStock;
}


//PUBLIC
//Metoda tøídy Tree
//	Vrátí vector se zkrachovalími spoleènostmi
vector<string> Tree::GetCompanies(uint16_t Option)
{
	vector<string> Result;


	switch (Option)
	{
	case 0:
	{
		return this->Companies;
	}
	case 1:
	{
		return this->GetExistCompanies();
	}
	case 2:
	{
		return this->GetNotExistCompanies();
	}
	default:
		return Result;
	}
}

//PRIVATE
//	Vrátí vector s existujicími spoleènostmi
vector<string> Tree::GetExistCompanies()
{
	vector<string> ExistCompanies;


	for(auto&& const Index : Companies)
	{
		if(DoesExist(Index))
		{
			ExistCompanies.push_back(Index);
		}
	}

	return ExistCompanies;
}

//PRIVATE
//	Vrátí vector s neexistujicími spoleènostmi
vector<string> Tree::GetNotExistCompanies()
{
	vector<string> NotExistCompanies;


	for (auto&& const Index : Companies)
	{
		if (!DoesExist(Index))
		{
			NotExistCompanies.push_back(Index);
		}
	}

	return NotExistCompanies;
}


//PUBLIC
//	Vrátí poèet akcií spoleènosti
uint64_t Tree::GetStocks(string Name)
{
	TreeItem* Root = GiveObjectOrNull(Name, this->Root);

	if (Root == nullptr || !Root->Exist)
	{
		return 0;
	}

	return Root->Stocks;
}