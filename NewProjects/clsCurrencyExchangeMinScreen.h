#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include"clsInputValidate.h"
class clsCurrencyExchangeMinScreen :protected clsScreen
{
private:
	enum enExchangeMenueOptions {
		enListCurrencies = 1,
		enFindCurrency = 2,
		enUpdateCurrency = 3,
		enCurrencyCalculator = 4,
		enMainMenue = 5
	};
	static short _ReadExchangeMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		short Choice = clsInputValidate::ReadIntNumberBetween(1, 5, "Enter Number between 1 to 5? ");
		return Choice;
	}
	static  void _GoBackToExchangeMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Transaction Menue...\n";

		system("pause>0");
		ShowExchangeMenue();
	}

	static void _ShowListScreen() {

		cout << "list screen will be here";
	}
	static void _ShowFindScreen() {
		cout << "find screen will be here";
	}
	static void _ShowUpdateRateScreen() {
		cout << " update screen will be here";
	}
	static void _ShowCurrencyCalculatorScreen() {

		cout << " currency calculator will be here";
	}

	static void _PerfromCurrencyExchangeMenueOptions(enExchangeMenueOptions ExchangeMenueOptions) {

		switch (ExchangeMenueOptions) {
		case enExchangeMenueOptions::enListCurrencies:
			system("cls");
			_ShowListScreen();
			_GoBackToExchangeMenue();
			break;
		case enExchangeMenueOptions::enFindCurrency:
			system("cls");
			_ShowFindScreen();
			_GoBackToExchangeMenue();
			break;
		case enExchangeMenueOptions::enUpdateCurrency:
			system("cls");
			_ShowUpdateRateScreen();
			_GoBackToExchangeMenue();
			break;
		case enExchangeMenueOptions::enCurrencyCalculator:
			system("cls");
			_ShowCurrencyCalculatorScreen();
			_GoBackToExchangeMenue();
			break;
		case enExchangeMenueOptions::enMainMenue:
			break;
		}
	}
public:
	static void ShowExchangeMenue()
	{
		if (!CheckAccessRights(clsUser::pCurrencyExchange))
		{
			return;
		}

		system("cls");
		_DrawScreenHeader("\tCurrency Exchange Main Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\tCurrency Exchange Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t\t[5] Main Menue.\n";

		cout << setw(37) << left << "" << "===========================================\n";

		_PerfromCurrencyExchangeMenueOptions((enExchangeMenueOptions)_ReadExchangeMenueOption());
	}
};

