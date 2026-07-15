#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include"clsBankClient.h"
#include <iomanip>
class clsDeleteClientScreen :protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }


public:
   static void ShowDeleteClientScreen() {

       _DrawScreenHeader("\tDelete Client Screen");

        string AccountNumber = "";
        cout << "\nPlease Enter client account number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber)) {

            cout << "\nAccount number is not found choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        cout << "\nAre you sure you want to delete this client y/n? ";

        char Answer;
        cin >> Answer;
        while (Answer != 'Y' && Answer != 'y' && Answer != 'n' && Answer != 'N') {

            cout << "Invalid choice! Please select Y or N: ";
            cin >> Answer;
        }

        if (Answer == 'y' || Answer == 'Y')
        {
            if (Client.Delete())
            {
                cout << "\nClient deleted successfully :-)";
            }
            else
            {
                cout << "\nError Client was not deleted\n";

            }
        }
        else
            cout << "\nClient deletion process cancelled.\n";


    }



};

