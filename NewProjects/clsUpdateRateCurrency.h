#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsCurrency.h"

class clsUpdateRateCurrency : protected clsScreen
{
private:
    static void _PrintCurrencyCard(clsCurrency Currency) {

        cout << "\nCurrency Card:";
        cout << "\n___________________";
        cout << "\nCountry  : " << Currency.Country();
        cout << "\nCode     : " << Currency.CurrencyCode();
        cout << "\nName     : " << Currency.CurrencyName();
        cout << "\nRate(1$) : " << Currency.Rate();
        cout << "\n___________________\n";
    }

    
    static string _ReadCurrencyCode() {

        string CurrencyCode;
        cout << "\nPlease Enter Currency Code: ";
        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, Enter another code: ";
            CurrencyCode = clsInputValidate::ReadString();
        }
        return CurrencyCode;
    }

public:

    static void ShowUpdateRateCurrency() {

        _DrawScreenHeader("\tUpdate Currency Rate Screen");

        string CurrencyCode = _ReadCurrencyCode();
        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

        _PrintCurrencyCard(Currency);

        char Answer = 'n';
        cout << "\nAre you sure you want to update the rate of this currency y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            cout << "\nEnter New Rate: ";
            float NewRate = clsInputValidate::ReadDblNumber();

            Currency.UpdateRate(NewRate);

            cout << "\nCurrency Rate Updated Successfully :-)\n";
            _PrintCurrencyCard(Currency);
        }
        else
        {
            cout << "\nThe operation has been canceled.\n";
        }
    }
};