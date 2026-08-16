#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
class clsFindCurrencyScreen :protected clsScreen
{
private:

	enum enFindCurrencyOption { Code = 1, Country = 2 };

	static void _PrintCurrencyCard(clsCurrency Currency) {

		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nCountry  : " << Currency.Country();
		cout << "\nCode     : " << Currency.CurrencyCode();
		cout << "\nName     : " << Currency.CurrencyName();
		cout << "\nRate(1$) : " << Currency.Rate();
		cout << "\n___________________\n";
	}
	static void _CurrencyIsFound(clsCurrency Currency){
		if (Currency.IsEmpty())
		{
			cout << "\nCurrency is Not Found!\n";
		}
		else
		{
			cout << "\nCurrency is Found :)\n\n";
			_PrintCurrencyCard(Currency);
		}
		
	}
	static short _ReadBy() {
		cout << "Find By: [1] Code or [2] Country? ";
		short Num = clsInputValidate::ReadIntNumberBetween(1, 2);
		return Num;

	}
	static string _ReadCurrencyCountry() {

		cout << "Plase Enter Currency Country? ";
		string Country = clsInputValidate::ReadString();

		return Country;
	}
	static string _ReadCurrencyCode() {

		cout << "Plase Enter Currency Code? ";
		string Code = clsInputValidate::ReadString();
		return Code;
	}

public:

	static void FindCurrencyScreen() {

		_DrawScreenHeader("\tFind Currency Screen");

		switch (_ReadBy()) {

		case enFindCurrencyOption::Code:
			_CurrencyIsFound(clsCurrency::FindByCode(_ReadCurrencyCode()));
			break;
		case enFindCurrencyOption::Country:
			_CurrencyIsFound(clsCurrency::FindByCountry(_ReadCurrencyCountry()));
			break;
		}

	}
};

