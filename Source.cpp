//Tree.h knihovny
//	#include <iostream>
//	#include <string>
//	#include <vector>
#include <time.h>
#include <locale.h>  
#include <thread>
#include <chrono>
#include <cstdlib>//clear cls


#include "User.h"
#include "List.h"
#include "Tree.h"

//Tree.h namespace
//using namespace std;



void PrintLetter(char Letter, uint16_t Count)
{
	cout << "\t\t";
	for (uint16_t i = 0; i < Count; i++) {
		cout << Letter;
	}
}

void CleanConsole(int Seconds)
{
	this_thread::sleep_for(chrono::seconds(Seconds));

	system("cls");
	//system("clear"); Linux
}

void PrintCompanies(Tree* tree)
{
	PrintLetter('*', 90);
	
	cout << endl;

	tree->Print();
	
	cout << endl << endl;
}

void PrintInvestment(List* list)
{
	if (list->GetCount())
	{
		list->Print();
	}

	PrintLetter('*', 90);

	cout << endl;
}

void PrintUser(User* user)
{
	cout <<"\t\t"<< user->GetName() << " (pen�ze): " << user->GetMoney() << " K�" << endl;
}

void PrintNotExistCompanies(Tree* tree)
{
	vector<string> NotExistCompanies = tree->GetCompanies(2);


	if(NotExistCompanies.size() == 0)
	{
		return;
	}

	
	cout << endl << "\t\tSrde�n� vzpom�n�me: ";
	
	uint16_t Index = 0;
	for (auto && const Name : NotExistCompanies) {
		if (Index == 6) {
			cout << endl << "\t\t";
			Index = 0;
		}			
		cout << Name << " ";

		Index++;
	}

	cout << endl;
}


bool BuyInvestment(Tree* tree, User* user, List* list, string Name, uint64_t Stocks)
{
	uint64_t CompanyStocks = tree->GetStocks(Name); 
	uint64_t UserMoney = user->GetMoney();

	int64_t CompanyPerStock = tree->GetPerStock(Name);


	if (CompanyStocks < Stocks || UserMoney < Stocks * CompanyPerStock)
	{
		return false;
	}

	tree->BuyStocks(Name, Stocks);
	(list->DoesExist(Name)) ? list->InsertTo(Name, Stocks) : list->Insert(Name, Stocks, tree);
	user->SetMoney(UserMoney - Stocks * CompanyPerStock);
	
	return true;
	
}


void Print(Tree* tree, List* list, User* user) {
	//Vyp�e v�echny spole�nosti
	PrintCompanies(tree);
	//Vyp�e v�echny zkrachoval� spole�nosti
	PrintNotExistCompanies(tree);
	//Vyp�e seznam investic
	PrintInvestment(list);
	//Vyp�e data u�ivatele
	PrintUser(user);
}


void AfterMonth(uint64_t Months, List* list, Tree* tree, User* user)
{
	for (uint64_t i = Months; i > 0; i--)
	{
		CleanConsole(5);

		tree->ChangeMonth();
		list->ChangePerMonth(tree);

		Print(tree, list, user);

		cout << "\t\tZb�v� m�s�c�: " << i - 1;

		if (tree->GetCompanies(1).size() == 0)
		{
			return;
		}
	}
}



int main()
{
	setlocale(LC_ALL, "");
	srand((int)time(NULL));
	
	string Jmeno;
	string Prijmeni;

	uint64_t Money;

	uint16_t Difficulty;
	uint16_t Option;

	User* user;

	Tree* tree;

	List* list;


	PrintLetter('*', 90);

	cout << endl << endl << "\t\tJm�no: ";
	cin >> Jmeno >> Prijmeni;

	cout << "\t\tPen�z na ��tu: ";
	cin >> Money;

	user = new User(Jmeno +' '+ Prijmeni, Money);

	cout << "\t\tObt�nost[1-3]: ";
	cin >> Difficulty;


	if (Difficulty <= 0 || Difficulty > 3)
	{
		Difficulty = 2;
	}


	cout << endl << endl << "\t\tPopis:";
	cout << endl << endl << "\t\t��elem tohoto programu je simulace Investic." << endl;
	cout << "\t\tA vy v t�to simulaci hrajete velkou roli a to Investora" << endl;
	cout << "\t\tkter� mus� investovat pen�ze do r�zn�ch spole�nost� aby si vyd�lal na �ivot.";
	cout << endl << endl << endl << "\t\tAutor:";
	cout << endl << endl << "\t\tJan Kus�k, Login::Kus0054";
	cout << endl << endl << endl;
	PrintLetter('*', 90);

	cout << endl;


	CleanConsole(10);
	
	tree = new Tree("Spolecnosti", Difficulty);
	list = new List();
	
	do {
		Print(tree,list,user);

		cout << "\t\t(1) Investovat    " << "(2) Prodat    " <<"(3) Poposko�it    " <<"(4) Ukon�it" << endl;
		cout << "\t\tVolba: ";
		cin >> Option;


		switch (Option)
		{
		case 1: 
		{
			string Name;

			uint64_t Stocks;


			CleanConsole(0);

			Print(tree,list,user);

			cout << "\t\tN�zev spole�nosti: ";
			cin >> Name;
			cout << "\t\tPo�et Akci�(Koupit): ";
			cin >> Stocks;
			cout << "\t\t";


			for (auto && const Index : tree->GetCompanies(1))
			{
				if (Name == Index)
				{
					BuyInvestment(tree, user, list, Name, Stocks)
						? cout << "Obchod �sp�n� uzav�en"
						: cout << "Nic takov�ho!!";

					break;
				}
			}

			CleanConsole(1);
			break;
		}
		case 2: 
		{
			string Name;

			uint64_t Stocks;


			CleanConsole(0);

			Print(tree, list, user);

			cout << "\t\tN�zev spole�nosti: ";
			cin >> Name;
			cout << "\t\tPo�et Akci�(Prodat): ";
			cin >> Stocks;
			cout << "\t\t";

		
			if (list->DoesExist(Name) && Stocks <= list->GetStocks(Name))
			{
				uint64_t Money = list->Remove(Name, Stocks);


				tree->ReturnStocks(Name, Stocks);

				if (Money > 100000 && list->GetDuration(Name) <36)
				{
					user->SetMoney(user->GetMoney() + Money / 100 * 85);
					cout << "Obchod �sp�n� uzav�en s dan�!" << endl << "\t\tNa ��et: " << Money << "K�";
				}
				else
				{
					user->SetMoney(user->GetMoney() + Money);
					cout << "Obchod �sp�n� uzav�en bez dan�!" << endl << "\t\tNa ��et: " << Money << "K�";
				}				
			}
			else
			{
				cout << "Nic takov�ho!!";
			}

			CleanConsole(2);
			break;
		}
		case 3:
		{
			uint64_t Months;


			CleanConsole(0);

			Print(tree, list, user);

			cout << "\t\tM�s�c�: ";
			cin >> Months;

			AfterMonth(Months, list, tree, user);
			

			if (tree->GetCompanies(1).size() == 0)
			{
				CleanConsole(0);

				cout << endl << endl << endl << endl;
				cout << "\t\t\tKonec Simulace" << endl;
				cout << "\t\t\tStav pen�z: " << user->GetMoney() << endl;
				cout << "\t\t\tGratuluji k tak skv�l�mu v�konu " << user->GetName() << endl;
				PrintLetter('/', 55);

				CleanConsole(5);

				Option = 4;

				break;
			}
			else
			{
				CleanConsole(1);
			}
			break;
		}
		case 4:
		{
			break;
		}
		default:
			break;
		}

	} while (Option != 4);


	delete user, list, tree;
	user = nullptr;
	list = nullptr;
	tree = nullptr;

	return 0;
}