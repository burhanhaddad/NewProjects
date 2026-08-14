#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include"clsMainScreen.h"
#include"clsDepositScreen.h"
#include"clsWithdrawScreen.h"
#include"clsTotalBalanceScreen.h"
#include"clsTransferScreen.h"
#include"clsTrasferLogScreen.h"
class clsTransactionsScreen :protected clsScreen
{
private:
	enum enTransactionsMenueOptions {
		enDeposit = 1,
		enWithdraw = 2,
		enTotalBalance = 3,
		enTransfer = 4,
		enTransferLog = 5,
		enMainMenue = 6

	};

	static short _ReadTransactionMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short Choice = clsInputValidate::ReadIntNumberBetween(1, 6, "Enter Number between 1 to 6? ");
		return Choice;
	}

	static  void _GoBackToTransactionMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Transaction Menue...\n";

		system("pause>0");
		ShowTransactionsMenue();
	}

	static void _ShowDepositScreen(){
	
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen() {

		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalancesScreen()
	{
		clsTotalBalanceScreen::ShowTotalBalances();
	}
	static void _ShowTransferScreen() {

		clsTransferScreen::ShowTransferScreen();
	}
	static void _ShowTransferLogScreen() {

		clsTrasferLogScreen::ShowTransferLogScreen();

	}

	static void _PerfromTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOptions) {

		switch(TransactionsMenueOptions){

		case enTransactionsMenueOptions::enDeposit:
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionMenue();
			break;
		case enTransactionsMenueOptions::enWithdraw:
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionMenue();
			break;
		case enTransactionsMenueOptions::enTotalBalance:
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionMenue();
			break;
		case enTransactionsMenueOptions::enTransfer:
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionMenue();
			break;
		case enTransactionsMenueOptions::enTransferLog:
			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransactionMenue();
			break;
		case enTransactionsMenueOptions::enMainMenue:
			
			break;
		}

	}
public:


	static void ShowTransactionsMenue()
	{
		if (!CheckAccessRights(clsUser::pTransactionsList))
		{
			return;
		}

		system("cls");
		_DrawScreenHeader("\tTransaction Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\tTransaction Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t\t[3] Total Balances.\n";
		cout << setw(37) << left << "" << "\t\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t\t[5] Transfer Log.\n";
		cout << setw(37) << left << "" << "\t\t[5] Main Menue.\n";
	
		cout << setw(37) << left << "" << "===========================================\n";

		_PerfromTransactionsMenueOption((enTransactionsMenueOptions)_ReadTransactionMenueOption());
	}


};

