#pragma once
#include<iostream>
#include<string>
#include"clsString.h"
#include"clsPerson.h"
#include<vector>
#include<fstream>

using namespace std;

class clsBankClient : public clsPerson
{
private:
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
    bool _MarkForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line, string Separator) {

   
        if (Line == "") {
            return _GetEmptyClientObject();
        }
		vector<string>vClientData;
		vClientData = clsString::Split(Line, Separator);
        
        
       
		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
	}
    static string _ConvertClientObjectToLine(clsBankClient Client,string Separator = "#//#") {

        string S1 = "";
        S1 += Client.FirstName + Separator;
        S1 += Client.LastName + Separator;
        S1 += Client.Email + Separator;
        S1 += Client.Phone + Separator;
        S1 += Client.AccountNumber() + Separator;
        S1 += Client.PinCode + Separator;
        S1 += to_string(Client.AccountBalance);
        return S1;
    }

	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

    static vector<clsBankClient> _LoadClientDataFromFile() {

        vector <clsBankClient>vClients;

        fstream MyFile;

        MyFile.open("Clients.txt", ios::in);//read mode
        if (MyFile.is_open())
        {
            
            string Line;
            while (getline(MyFile, Line)) {

                clsBankClient Client = _ConvertLineToClientObject(Line, "#//#");
                vClients.push_back(Client);
            }
            MyFile.close();

            
        }
        return vClients;
    }
    static void _SaveDataToFile(vector<clsBankClient> vClients){

        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);
        if (MyFile.is_open())
        {
            string Line;
            for (clsBankClient C : vClients) {

                if (C.MarkForDelete() == false)
                {
                    Line = clsBankClient::_ConvertClientObjectToLine(C);
                    MyFile << Line << endl;
                }

            }
        }
        MyFile.close();
        
    }
    void AddDataToFile(string DataLine) {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::app);
        if (MyFile.is_open())
        {
            MyFile << DataLine << endl;

        }
    }
    void _Update() {

        vector <clsBankClient>vClients;
        vClients = _LoadClientDataFromFile();

        for (clsBankClient &C : vClients) {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }
        }
        _SaveDataToFile(vClients);
    }
    void _AddNew() {

        AddDataToFile(_ConvertClientObjectToLine(*this));
    }
public:
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance)
		:clsPerson(FirstName, LastName, Email, Phone) 
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_AccountBalance = AccountBalance;
        _PinCode = PinCode;
	}

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }
    bool MarkForDelete() {
        return _MarkForDelete;
    }

    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    //void Print()
    //{
    //    cout << "\nClient Card:";
    //    cout << "\n___________________";
    //    cout << "\nFirstName   : " << FirstName;
    //    cout << "\nLastName    : " << LastName;
    //    cout << "\nFull Name   : " << FullName();
    //    cout << "\nEmail       : " << Email;
    //    cout << "\nPhone       : " << Phone;
    //    cout << "\nAcc. Number : " << _AccountNumber;
    //    cout << "\nPassword    : " << _PinCode;
    //    cout << "\nBalance     : " << _AccountBalance;
    //    cout << "\n___________________\n";

    //}

    static clsBankClient Find(string AccountNumber) {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line)) {

                clsBankClient Client = _ConvertLineToClientObject(Line,"#//#");

                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                    
                }
            }
            
        }


        return _GetEmptyClientObject();

    }
    static clsBankClient Find(string AccountNumber,string PinCode) {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line)) {

                clsBankClient Client = _ConvertLineToClientObject(Line, "#//#");

                if (Client.AccountNumber() == AccountNumber && Client._PinCode == PinCode)
                {

                    MyFile.close();
                    return Client;

                }
            }
            
        }
        return _GetEmptyClientObject();




    }
    enum enSaveResult { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists };

    bool Delete() {
        vector <clsBankClient> vClients;
        vClients = _LoadClientDataFromFile();

        for (clsBankClient& C : vClients) {

            if (C.AccountNumber() == _AccountNumber)
            {
                C._MarkForDelete = true;
                break;
            }

        }
        _SaveDataToFile(vClients);
        *this = _GetEmptyClientObject();
        return true;
    }
    enSaveResult Save() {

        switch (_Mode) {

        case enMode::EmptyMode:
            if (IsEmpty())
            {
                return enSaveResult::svFaildEmptyObject;
            }
            
        case enMode::UpdateMode:
            _Update();
            return enSaveResult::svSucceeded;
            break;
            
        case enMode::AddNewMode:

            if (IsClientExist(_AccountNumber))
            {
                return enSaveResult::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();
                _Mode = enMode::UpdateMode;
                return enSaveResult::svSucceeded;
            }
            break;
        }
    }
    static bool IsClientExist(string AccountNumber) {

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        return (!Client.IsEmpty());
    }

    static clsBankClient GetAddNewClient(string AccountNumber) {

        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }



    static vector <clsBankClient>GetClientsList() {

        return _LoadClientDataFromFile();
    }

    static float GetTotalBalances() {

        vector <clsBankClient>vClients;
        vClients = _LoadClientDataFromFile();

        double TotalBalances = 0;
        for (clsBankClient& C : vClients) {

            TotalBalances += C.AccountBalance;
        }
        return TotalBalances;
    }

    void Deposit(double Amount) {

        _AccountBalance += Amount;
        Save();
    }

    bool Withdraw(double Amount) {

        if (Amount > _AccountBalance)
        {
            return false;
        }
        else
        {
           
            _AccountBalance -= Amount;
            Save();
        }
    }

};

