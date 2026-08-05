#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include"Global.h"
#include "clsMainScreen.h"
class clsLoginScreen :protected clsScreen
{
private:
	static bool _Login() {
	
		
		short FaildLoginCount = 0;
		bool LoginFaild = false;
		string UserName, Password;

		do
		{
			

			if (LoginFaild)

				
			{
				FaildLoginCount++;
				cout << "\n Invalid User Name or Password, please try again :-)\n";
				cout << "\nYou have " << (3 - FaildLoginCount) << " trials left.\n";
			}
			if (FaildLoginCount == 3)
			{
				cout << "\nYou have exceeded the maximum number of trials, please try again later.\n";
				return false;
			}


			cout << "\nPlease enter User Name: ";
			cin >> UserName;
			cout << "\nPlease enter Password: ";
			cin >> Password;
			CurrentUser = clsUser::Find(UserName, Password);
			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);
		clsMainScreen::ShowMainMenue();
		return true;
	}
public:


	static bool ShowLoginScreen() {

		system("cls");
		_DrawScreenHeader("\tLogin Screen");
		return _Login();
	}
};

