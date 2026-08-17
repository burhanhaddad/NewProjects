#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsCurrency.h"
class clsCalculateCurrencyScreen : protected clsScreen
{
private:
	static string _ReadCurrencyCode() {

		string CurrencyCode = clsInputValidate::ReadString();
		while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
			
			cout << "\nCurrency not found, please enter a valid currency: ";

			CurrencyCode = clsInputValidate::ReadString();
		}
		return CurrencyCode;
	}

	static float _ReadCurrencyRate(string CurrencyCode) {

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return Currency.Rate();
	}

public:

	static void _ShowCalculateCurrencyScreen() {


		clsCurrency Currency1 = clsCurrency::FindByCode(_ReadCurrencyCode());

		clsCurrency Currency2 = clsCurrency::FindByCode("usd");

		clsCurrency Currency3 = clsCurrency::FindByCode(_ReadCurrencyCode());
	}
};

