#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include"clsUserSListScreen.h"
#include"clsAddNewUserScreen.h" 
#include"clsDeleteUserScreen.h"
#include"clsUpdateUserScreen.h"
#include"clsFindUserScreen.h"
class clsManageUserScreen : protected clsScreen
{
private:

	enum enManageUserMenueOptions {
		eListUUser = 1,
		eAddNewUser = 2,
		eDeleteUser = 3,
		eUpdateUser = 4,
		eFindUser = 5,
		eMainMenue = 6

	};

	static short _ReadManageMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short Choice = clsInputValidate::ReadIntNumberBetween(1, 6, "Enter Number between 1 to 6? ");
		return Choice;
	}
	static  void _GoBackToManageUserMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Manage user Menue...\n";

		system("pause>0");
		ShowManageUserMenue();
	}

	static void _ShowLisUserScreen() {

		clsListUsersScreen::ShowUsersList();
	}

	static void _ShowAddNewScreen() {

		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteScreen() {

		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateScreen() {

		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindScreen() {

		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _PerfromManageUserMenueOption(enManageUserMenueOptions ManageUserMenueOptions) {

		switch (ManageUserMenueOptions) {

		case enManageUserMenueOptions::eListUUser:
			system("cls");
			_ShowLisUserScreen();
			_GoBackToManageUserMenue();
			break;
		case enManageUserMenueOptions::eAddNewUser:
			system("cls");
			_ShowAddNewScreen();
			_GoBackToManageUserMenue();		
			break;
		case enManageUserMenueOptions::eDeleteUser:
			system("cls");
			_ShowDeleteScreen();
			_GoBackToManageUserMenue();
			break;
		case enManageUserMenueOptions::eUpdateUser:
			system("cls");
			_ShowUpdateScreen();
			_GoBackToManageUserMenue();
			break;
		case enManageUserMenueOptions::eFindUser:
			system("cls");
			_ShowFindScreen();
			_GoBackToManageUserMenue();
			break;
		case enManageUserMenueOptions::eMainMenue:
			break;

		}
	}

public:

	static void ShowManageUserMenue()
	{
		if (!CheckAccessRights(clsUser::pManageUsers))
		{
			return;
		}
		system("cls");
		_DrawScreenHeader("\tManage User Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\tManage User Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t[1] List Users.\n";
		cout << setw(37) << left << "" << "\t\t[2] Add New User.\n";
		cout << setw(37) << left << "" << "\t\t[3] Delete User.\n";
		cout << setw(37) << left << "" << "\t\t[4] Update User.\n";
		cout << setw(37) << left << "" << "\t\t[5] Find User.\n";
		cout << setw(37) << left << "" << "\t\t[6] Main Menue.\n";
		
		cout << setw(37) << left << "" << "===========================================\n";

		_PerfromManageUserMenueOption((enManageUserMenueOptions)_ReadManageMenueOption());
	}
};
