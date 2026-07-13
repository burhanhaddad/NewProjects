
#include<iostream>
#include<vector>
#include"clsString.h"
#include "clsUtil.h"
#include"clsInputValidate.h"
#include"clsDate.h"
#include"clsBankClient.h"
#include"clsMainScreen.h"

using namespace std;


void ReadClientInfo(clsBankClient& Client) {

    cout << "\nEnter FirstName: ";
    Client.FirstName = clsInputValidate::ReadString();
    cout << "\nEnter LastName: ";
    Client.LastName = clsInputValidate::ReadString();
    cout << "\nEnter Email: ";
    Client.Email = clsInputValidate::ReadString();
    cout << "\nEnter Phone: ";
    Client.Phone = clsInputValidate::ReadString();
    cout << "\nEnter PinCode: ";
    Client.PinCode = clsInputValidate::ReadString();
    cout << "\nEnter AccountBalance: ";
    Client.AccountBalance = clsInputValidate::ReadFloatNumber();
}
void UpdateClient() {
    string AccountNumber = "";
    cout << "\nPlease Enter client account number: ";
    AccountNumber = clsInputValidate::ReadString();

    while (!clsBankClient::IsClientExist(AccountNumber)) {

        cout<<"\nAccount number is not found choose another one: ";
        AccountNumber = clsInputValidate::ReadString();
    }

    clsBankClient Client = clsBankClient::Find(AccountNumber);
    Client.Print();

    ReadClientInfo(Client);

    clsBankClient::enSaveResult SaveResult;

    SaveResult = Client.Save();

    switch(SaveResult){
    
    case clsBankClient::enSaveResult::svFaildEmptyObject:
        cout << "\n Error account was not saved because it's Empty:";
        break;
    case clsBankClient::enSaveResult::svSucceeded:
        cout << "\n Account updated successfully :-)\n";
        Client.Print();
        break;

    }

}
void AddNewClient() {
    string AccountNumber = "";
    cout << "\nPlease Enter client account number: ";
    AccountNumber = clsInputValidate::ReadString();

    while (clsBankClient::IsClientExist(AccountNumber)) {

        cout << "\nAccount Number Is Already Used, choose another one: ";
        AccountNumber = clsInputValidate::ReadString();
    }
    clsBankClient NewClient = clsBankClient::GetAddNewClient(AccountNumber);
    ReadClientInfo(NewClient);
    clsBankClient::enSaveResult SaveResult;
    SaveResult = NewClient.Save();


    switch (SaveResult)
    {
    case  clsBankClient::enSaveResult::svSucceeded:
    {
        cout << "\nAccount Addeded Successfully :-)\n";
        NewClient.Print();
        break;
    }
    case clsBankClient::enSaveResult::svFaildEmptyObject:
    {
        cout << "\nError account was not saved because it's Empty";
        break;

    }
    case clsBankClient::enSaveResult::svFaildAccountNumberExists:
    {
        cout << "\nError account was not saved because account number is used!\n";
        break;

    }
    }

}
void DeleteClient() {

    string AccountNumber = "";
    cout << "\nPlease Enter client account number: ";
    AccountNumber = clsInputValidate::ReadString();

    while (!clsBankClient::IsClientExist(AccountNumber)) {

        cout << "\nAccount number is not found choose another one: ";
        AccountNumber = clsInputValidate::ReadString();
    }

    clsBankClient Client = clsBankClient::Find(AccountNumber);
    Client.Print();

    cout << "\nAre you sure you want to delete this client y/n? ";

    char Answer ;
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





void PrintClientRecordBalanceLine(clsBankClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber();
    cout << "| " << setw(40) << left << Client.FullName();
    cout << "| " << setw(12) << left << Client.AccountBalance;

}


void ShowTotalBalances()
{

    vector <clsBankClient> vClients = clsBankClient::GetClientsList();

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double TotalBalances = clsBankClient::GetTotalBalances();

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (clsBankClient Client : vClients)
        {
            PrintClientRecordBalanceLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t   Total Balances = " << TotalBalances << endl;
    cout << "\t\t\t\t   ( " << clsUtil::NumberToText(TotalBalances) << ")";
}

int main()
{
    clsMainScreen::ShowMainMenue();
}
