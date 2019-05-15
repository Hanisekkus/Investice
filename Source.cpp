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
	cout <<"\t\t"<< user->GetName() << " (peníze): " << user->GetMoney() << " Kè" << endl;
}

void PrintNotExistCompanies(Tree* tree)
{
	vector<string> NotExistCompanies = tree->GetCompanies(2);


	if(NotExistCompanies.size() == 0)
	{
		return;
	}

	
	cout << endl << "\t\tSrdeènì vzpomínáme: ";
	
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
	//Vypíše všechny spoleènosti
	PrintCompanies(tree);
	//Vypíše všechny zkrachovalé spoleènosti
	PrintNotExistCompanies(tree);
	//Vypíše seznam investic
	PrintInvestment(list);
	//Vypíše data uživatele
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

		cout << "\t\tZbývá mìsícù: " << i - 1;

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

	cout << endl << endl << "\t\tJméno: ";
	cin >> Jmeno >> Prijmeni;

	cout << "\t\tPenìz na úètu: ";
	cin >> Money;

	user = new User(Jmeno +' '+ Prijmeni, Money);

	cout << "\t\tObtížnost[1-3]: ";
	cin >> Difficulty;


	if (Difficulty <= 0 || Difficulty > 3)
	{
		Difficulty = 2;
	}


	cout << endl << endl << "\t\tPopis:";
	cout << endl << endl << "\t\tÚèelem tohoto programu je simulace Investic." << endl;
	cout << "\t\tA vy v této simulaci hrajete velkou roli a to Investora" << endl;
	cout << "\t\tkterý musí investovat peníze do rùzných spoleèností aby si vydìlal na život.";
	cout << endl << endl << endl << "\t\tAutor:";
	cout << endl << endl << "\t\tJan Kusák, Login::Kus0054";
	cout << endl << endl << endl;
	PrintLetter('*', 90);

	cout << endl;


	CleanConsole(10);
	
	tree = new Tree("Spolecnosti", Difficulty);
	list = new List();
	
	do {
		Print(tree,list,user);

		cout << "\t\t(1) Investovat    " << "(2) Prodat    " <<"(3) Poposkoèit    " <<"(4) Ukonèit" << endl;
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

			cout << "\t\tNázev spoleènosti: ";
			cin >> Name;
			cout << "\t\tPoèet Akcií(Koupit): ";
			cin >> Stocks;
			cout << "\t\t";


			for (auto && const Index : tree->GetCompanies(1))
			{
				if (Name == Index)
				{
					BuyInvestment(tree, user, list, Name, Stocks)
						? cout << "Obchod úspìšnì uzavøen"
						: cout << "Nic takového!!";

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

			cout << "\t\tNázev spoleènosti: ";
			cin >> Name;
			cout << "\t\tPoèet Akcií(Prodat): ";
			cin >> Stocks;
			cout << "\t\t";

		
			if (list->DoesExist(Name) && Stocks <= list->GetStocks(Name))
			{
				uint64_t Money = list->Remove(Name, Stocks);


				tree->ReturnStocks(Name, Stocks);

				if (Money > 100000 && list->GetDuration(Name) <36)
				{
					user->SetMoney(user->GetMoney() + Money / 100 * 85);
					cout << "Obchod úspìšnì uzavøen s daní!" << endl << "\t\tNa úèet: " << Money << "Kè";
				}
				else
				{
					user->SetMoney(user->GetMoney() + Money);
					cout << "Obchod úspìšnì uzavøen bez danì!" << endl << "\t\tNa úèet: " << Money << "Kè";
				}				
			}
			else
			{
				cout << "Nic takového!!";
			}

			CleanConsole(2);
			break;
		}
		case 3:
		{
			uint64_t Months;


			CleanConsole(0);

			Print(tree, list, user);

			cout << "\t\tMìsícù: ";
			cin >> Months;

			AfterMonth(Months, list, tree, user);
			

			if (tree->GetCompanies(1).size() == 0)
			{
				CleanConsole(0);

				cout << endl << endl << endl << endl;
				cout << "\t\t\tKonec Simulace" << endl;
				cout << "\t\t\tStav penìz: " << user->GetMoney() << endl;
				cout << "\t\t\tGratuluji k tak skvìlému výkonu " << user->GetName() << endl;
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