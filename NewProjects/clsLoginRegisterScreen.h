#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>

class clsLoginRegisterScreen :protected clsScreen
{
private:

    static void PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord LoginRegisterRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(35) << left << LoginRegisterRecord.Date;
        cout << "| " << setw(20) << left << LoginRegisterRecord.UserName;
        cout << "| " << setw(20) << left << LoginRegisterRecord.Password;
        cout << "| " << setw(10) << left << LoginRegisterRecord.Permissions;
        cout << "  | " << setw(10) << left << (LoginRegisterRecord.LoginSucceed ? "Success" : "Failed");

    }

public:

    static void ShowLoginRegisterScreen() {

        vector <clsUser::stLoginRegisterRecord> vLoginRegisterRecord = clsUser::GetLoginRegisterList();

        string Title = "\tLogin Register Screen";
        string SubTitle = "\t\t(" + to_string(vLoginRegisterRecord.size()) + ") Record(s).";
        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << " | " << left << setw(10) << "Status";
        cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLoginRegisterRecord.size() == 0)
            cout << "\t\t\t\tNo Logins Available In the System!";
        else

            for (clsUser::stLoginRegisterRecord Record : vLoginRegisterRecord)
            {

                PrintLoginRegisterRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_________________________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};

