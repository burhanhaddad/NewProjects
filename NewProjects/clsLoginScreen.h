#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include"Global.h"
#include "clsMainScreen.h"
class clsLoginScreen :protected clsScreen
{
private:
	static void _Login() {
	
		bool LoginFaild = false;
		string UserName, Password;

		do
		{
			if (LoginFaild)
			{
				cout << "\nLogin Failed, Please try again :-(";
			}

			cout << "\nPlease enter User Name: ";
			cin >> UserName;
			cout << "\nPlease enter Password: ";
			cin >> Password;
			CurrentUser = clsUser::Find(UserName, Password);
			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);
		clsMainScreen::ShowMainMenue();
	}
public:
	static void ShowLoginScreen() {
		system("cls");
		_DrawScreenHeader("\tLogin Screen");
		_Login();
	}
};

