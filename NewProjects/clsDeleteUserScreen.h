#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include"clsUser.h"
class clsDeleteUserScreen : protected clsScreen
{
private:
	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n___________________\n";
	}
public:

	static void ShowDeleteUserScreen() {
		_DrawScreenHeader("\tDelete User Screen");
		string UserName = "";
		cout << "\nPlease Enter User Name: ";
		UserName = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(UserName)) {
			cout << "\nUser Name is not found choose another one: ";
			UserName = clsInputValidate::ReadString();
		}
		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);
		cout << "\nAre you sure you want to delete this user y/n? ";
		char Answer;
		cin >> Answer;
		while (Answer != 'Y' && Answer != 'y' && Answer != 'n' && Answer != 'N') {
			cout << "Invalid choice! Please select Y or N: ";
			cin >> Answer;
		}
		if (Answer == 'y' || Answer == 'Y')
		{
			if (User.Delete())
			{
				cout << "\nUser deleted successfully :-)";
			}
			else
			{
				cout << "\nError deleting user :-(\n";
			}
		}
	}
};

