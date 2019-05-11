#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <locale.h>  
#include <thread>
#include <chrono>
#include <cstdlib>//clear cls


#include "User.h"
#include "List.h"
#include "Tree.h"

using namespace std;


void PrintSpace(int Count) {
	for (int i = 0; i < Count; i++) {
		cout << "\t";
	}
}

void PrintLetter(char Letter, int Count) {
	PrintSpace(2);
	for (int i = 0; i < Count; i++) {
		cout << Letter;
	}
}

void PrintEnter(int Count) {
	for (int i = 0; i < Count; i++) {
		cout << endl;
	}
}

void CleanConsole(int Seconds) {
	this_thread::sleep_for(chrono::seconds(Seconds));
	system("cls");
	//system("clear"); Linux
}

void PrintCompanies(Tree* tree) {
	PrintLetter('*', 90);
	PrintEnter(2);
	tree->Print();
}

void PrintInvestment(List* list) {
	if (list->GetCount())
	{
		PrintEnter(1);
		list->Print();
		PrintEnter(1);
	}

	PrintLetter('*', 90);
	PrintEnter(1);
}

void PrintUser(User* user) {
	PrintSpace(2);
	cout << user->GetName() << " (peníze): " << user->GetMoney() << " Kè" << endl;
}

void PrintNoLonger(vector<string>NoLonger) {
	if (!NoLonger.empty()) {
		int Index = 0;
		cout << endl;
		PrintSpace(2);
		cout << "Srdeènì vzpomínáme: ";

		for (auto const&Name : NoLonger) {
			if (Index == 6) {
				cout << endl;
				PrintSpace(2);
				Index = 0;
			}			
			cout << Name << " ";
			Index++;
		}
		PrintEnter(1);
	}
}

void AfterMonth(unsigned long long int Months, List* list, Tree* tree,vector<string>&NoLonger) {

	for (unsigned long long int i = Months; i > 0; i--) {

		CleanConsole(0);

		tree->ChangeMonth();
		for (auto const &Name : tree->Delete()) {
			if (std::find(NoLonger.begin(), NoLonger.end(), Name) == NoLonger.end())
				NoLonger.push_back(Name);
		}
		list->ChangePerMonth(tree);

		PrintCompanies(tree);
		PrintNoLonger(NoLonger);
		PrintInvestment(list);

		PrintSpace(2);
		cout << "Zbývá mìsícù: " << i-1;

		if (tree->NothingExist()) {
			return;
		}
	}

}



int main() {
	setlocale(LC_ALL, "");
	srand((int)time(NULL));
	
	string Jmeno, Prijmeni;
	unsigned long long int Money;
	int Difficulty;

	PrintLetter('*', 90);
	PrintEnter(2);

	PrintSpace(2);
	cout << "Jméno: ";
	cin >> Jmeno >> Prijmeni;

	PrintSpace(2);
	cout << "Penìz na úètu: ";
	cin >> Money;

	User* user = new User(Jmeno +' '+ Prijmeni, Money);

	PrintSpace(2);
	cout << "Obtížnost[1-3]: ";
	cin >> Difficulty;
	if (Difficulty <= 0 || Difficulty > 3) Difficulty = 2;

	PrintEnter(2);
	PrintSpace(2);
	cout << "Popis:";
	PrintEnter(2);
	PrintSpace(2);
	cout << "Úèelem tohoto programu je simulace Investic." << endl;
	PrintSpace(2);
	cout << "A vy v této simulaci hrajete velkou roli a to Investora" << endl;
	PrintSpace(2);
	cout << "který musí investovat peníze do rùzných spoleèností aby si vydìlal na život.";
	PrintEnter(3);
	PrintSpace(2);
	cout << "Autor:";
	PrintEnter(2);
	PrintSpace(2);
	cout << "Jan Kusák, Login::Kus0054";
	PrintEnter(3);
	PrintLetter('*', 90);
	PrintEnter(1);

	CleanConsole(10);
	
	Tree* tree = new Tree("Spolecnosti", Difficulty);
	List* list = new List();
	int Option;
	vector<string> NoLonger;

	do {
		PrintCompanies(tree);
		PrintNoLonger(NoLonger);
		PrintInvestment(list);
		PrintUser(user);

		PrintSpace(2);
		cout << "(1) Investovat    " << "(2) Prodat    " <<"(3) Poposkoèit    " <<"(4) Ukonèit" << endl;
		PrintSpace(2);
		cout << "Volba: ";
		cin >> Option;


		switch (Option)
		{
		case 1: {
			string Name;
			unsigned long long int Stocks;

			CleanConsole(0);

			PrintCompanies(tree);
			PrintNoLonger(NoLonger);
			PrintInvestment(list);
			PrintUser(user);

			PrintSpace(2);
			cout << "Název spoleènosti: ";
			cin >> Name;
			PrintSpace(2);
			cout << "Poèet Akcií(Koupit): ";
			cin >> Stocks;

			PrintSpace(2);
			if (tree->DoesExist(Name) && tree->AvaibleStocks(Name, Stocks) && user->GetMoney() >= Stocks * tree->GetPerStock(Name)) {
				tree->BuyStocks(Name, Stocks);
				(list->DoesExist(Name)) ? list->InsertTo(Name, Stocks) : list->Insert(Name, Stocks, tree);
				user->SetMoney(user->GetMoney() - Stocks * tree->GetPerStock(Name));
				cout << "Obchod úspìšnì uzavøen";
			}
			else {
				cout << "Nic takového!!";
			}
			CleanConsole(1);
			break;
		}
		case 2: {
			string Name;
			unsigned long long int Stocks;

			CleanConsole(0);

			PrintCompanies(tree);
			PrintNoLonger(NoLonger);
			PrintInvestment(list);
			PrintUser(user);

			PrintSpace(2);
			cout << "Název spoleènosti: ";
			cin >> Name;
			PrintSpace(2);
			cout << "Poèet Akcií(Prodat): ";
			cin >> Stocks;

			PrintSpace(2);
		
			if (Stocks <= list->GetStocks(Name)&&list->DoesExist(Name))
			{
				tree->ReturnStocks(Name, Stocks);

				unsigned long long int Months = list->GetDuration(Name);
				unsigned long long int Money = list->Remove(Name, Stocks);

				if (Money > 100000 && Months <36)
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
		case 3:{
			unsigned long long int Months;

			CleanConsole(0);

			PrintCompanies(tree);
			PrintNoLonger(NoLonger);
			PrintInvestment(list);
			PrintUser(user);

			PrintSpace(2);
			cout << "Mìsícù: ";
			cin >> Months;
			AfterMonth(Months, list, tree, NoLonger);
			
			if (tree->NothingExist()) {
				CleanConsole(0);

				
				PrintEnter(4);
				PrintSpace(3);
				cout << "Konec Simulace" << endl;

				PrintSpace(3);
				cout << "Stav penìz: " << user->GetMoney() << endl;
				
				PrintSpace(3);
				cout << "Gratuluji k tak skvìlému výkonu " << user->GetName() << endl;

				PrintLetter('/', 55);
				CleanConsole(5);
				Option = 4;
				break;
			}
			else {
				CleanConsole(1);
			}
			break;
		}
		case 4:
		default:
			return 0;
		}

	} while (Option != 4);


	delete user, list, tree;
	user = nullptr;
	list = nullptr;
	tree = nullptr;

	return 0;
}