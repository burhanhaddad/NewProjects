
#include<iostream>
#include<vector>
#include"clsString.h"
#include "clsUtil.h"
#include"clsInputValidate.h"
#include"clsDate.h"
#include"clsBankClient.h"
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
int main()
{
   
    clsBankClient Client2 = clsBankClient::Find("A101");
    Client2.Print();    
}
