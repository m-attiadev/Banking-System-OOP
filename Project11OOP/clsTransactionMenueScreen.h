#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUtility.h"
#include "clsBankClient.h"
#include "clsMainScreen.h"
#include "clsDepostScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTransferScreen.h"
#include "clsTotalBalances.h"

using namespace std;

class clsTransactionMenueScreen : protected clsScreen
{

private:
	enum enTransactionMenueOptions {
		Deposit = 1, WhithDraw = 2, Transfer = 3, TotalBalances = 4, MainMenue = 5
	};

	static short _ReadChooseTransaction() {
		cout << clsUtil::GREEN << "\t\t\t\t\tChoose What do you want to do ? [1 to 5]? " << clsUtil::RESET;
		short Choose = clsInputValidate::ReadShortNumberBetween(1, 5, "Invalid Input, Enter agian Number Between 1 - 5");
		return Choose;
	}

	static void _GoBackToTransactionMenue() {
		cout << clsUtil::GREEN << "\n\t\t\t\t\tPress any key to go back to Transaction Menue..." << clsUtil::RESET;
		system("pause>0");
		ShowTransactionMenue();
	}

	static void _ShowDepostScreen() {
		clsDepostScreen::ShowDepostScreen();
	}

	static void _ShowWithdScreen() {
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTransferScreen() {
		clsTransferScreen::ShowTransferScreen();
	}

	static void _ShowTotalBalancesScreen() {
		clsTotalBalances::ShowTotalBalances();
	}

	static void _PerformanceTransactionMenueOptions(enTransactionMenueOptions enOption) {
		// ????? ????? ???? ???? ??? ????? ????? ???????
		if (enOption == clsTransactionMenueScreen::MainMenue)
			return;
		system("cls");
		switch (enOption) {
		case enTransactionMenueOptions::Deposit: {
			_ShowDepostScreen();
			break;
		}
		case enTransactionMenueOptions::WhithDraw: {
			_ShowWithdScreen();
			break;
		}
		case enTransactionMenueOptions::Transfer: {
			_ShowTransferScreen();
			break;
		}
		case enTransactionMenueOptions::TotalBalances: {
			_ShowTotalBalancesScreen();
			break;
		}
		case enTransactionMenueOptions::MainMenue: {
		}
		}
		// ??? ???? ??? ??? ?????? ?? ?? ???
		_GoBackToTransactionMenue();
	};

public:
	static void ShowTransactionMenue() {
		if (!CheckAccessRights(clsUser::enPermissions::pTransactionsMenue))
			return;

		system("cls");
		_DrawScreenHeader("Transaction Screen");
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t\tTransaction Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Depost.\n";
		cout << setw(37) << left << "" << "\t[2] WhithDraw.\n";
		cout << setw(37) << left << "" << "\t[3] Transfer.\n";
		cout << setw(37) << left << "" << "\t[4] Total Balances.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformanceTransactionMenueOptions((enTransactionMenueOptions)_ReadChooseTransaction());
	}
};
