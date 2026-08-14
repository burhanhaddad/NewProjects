#pragma once
#include<iostream>
#include<string>
#include"clsString.h"
#include"clsPerson.h"
#include<vector>
#include<fstream>
#include "clsUser.h"
#include "Global.h"
#include "clsString.h"
using namespace std;

class clsBankClient : public clsPerson
{
private:

    struct stTransferLogRecord;
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
    bool _MarkForDelete = false;

    static stTransferLogRecord _ConverTransferLogToRecord(string Line, string Separator = "#//#") {

        vector <string>vData;

        vData = clsString::Split(Line, Separator);
        stTransferLogRecord Record;
        Record.Date = vData[0];
        Record.SourceAccNumber = vData[1];
        Record.DestinationAccNumber = vData[2];
        Record.Amount = stof(vData[3]);
        Record.SourceBalance = stof(vData[4]);
        Record.DestinationBalance = stof(vData[5]);
        Record.UserName = (vData[6]);

        return Record;
    }

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


    string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient,
        string UserName, string Seperator = "#//#")
    {
        clsDate Date1 = clsDate::GetSystemDateTime();
        string TransferLogRecord = "";
        TransferLogRecord += Date1.DateTimeToString() + Seperator;
        TransferLogRecord += AccountNumber() + Seperator;
        TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
        TransferLogRecord += to_string(Amount) + Seperator;
        TransferLogRecord += to_string(AccountBalance) + Seperator;
        TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
        TransferLogRecord += UserName;
        return TransferLogRecord;
    }

    void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName)
    {

        string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

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
    
    struct stTransferLogRecord {
        string Date;
        string SourceAccNumber;
        string DestinationAccNumber;
        float Amount;
        float SourceBalance;
        float DestinationBalance;
        string UserName;

    };

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
			return true;
        }
    }
    bool Transfer(double Amount, clsBankClient& DestinationClient, string UserName) {

        if (Amount > AccountBalance) {
            return false;
        }
        Withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _RegisterTransferLog(Amount, DestinationClient, UserName);

    }

    static vector<stTransferLogRecord> GetTransferRegisterList() {

        vector <stTransferLogRecord>vData;
        fstream Myfile;
        Myfile.open("TransferLog.txt", ios::in);
        if (Myfile.is_open()) {

            string Line;
            while (getline(Myfile, Line)) {

               stTransferLogRecord Record =  _ConverTransferLogToRecord(Line);
               vData.push_back(Record);
            }
            Myfile.close();
        }
        
        return vData;
    }
    

};

