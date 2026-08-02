#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include"clsUser.h"
class clsFindUserScreen : protected clsScreen
{
private:
	static void _PrintUserCard(clsUser User)
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
		cout << "\n___________________\n";
	}
public:
	static void ShowFindUserScreen()
	{
		_DrawScreenHeader("\tFind User Screen");
		string UserName;
		cout << "\nPlease Enter User Name: ";
		UserName = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser name is not found, choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User1 = clsUser::Find(UserName);
		cout << "\nUser Found :-)\n";
		_PrintUserCard(User1);
	}
};

