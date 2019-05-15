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
	this->Companies.push_back(Name);


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

	for (auto const &company : Root->Leaves)
	{
		Print(company);
	}
}


//PUBLIC
//Metoda t��dy Tree
//	Zavol� priv�tn� metodu kter� zm�n� hodnoty ve strom�
void Tree::ChangeMonth()
{
	ChangeMonth(this->Root);
	Delete(false, this->Root);
}

//Metoda t��dy Tree
//	M�n� poka�d�m zavol�n� hodnoty ve strom�
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


//Metoda t��dy Tree
//	M�n� poka�d�m zavol�n� hodnoty ve strom�
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


//Metoda t��dy Tree
//	Vr�t� cenu za akcii dan� spole�nosti
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
//Metoda t��dy Tree
//	Vr�t� vector se zkrachoval�mi spole�nostmi
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
//	Vr�t� vector s existujic�mi spole�nostmi
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
//	Vr�t� vector s neexistujic�mi spole�nostmi
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
//	Vr�t� po�et akci� spole�nosti
uint64_t Tree::GetStocks(string Name)
{
	TreeItem* Root = GiveObjectOrNull(Name, this->Root);

	if (Root == nullptr || !Root->Exist)
	{
		return 0;
	}

	return Root->Stocks;
}