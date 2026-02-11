#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionMenueScreen.h"
#include "clsManageUsersScreen.h"
#include "Global.h"
#include "clsUser.h"
#include "clsLogRegisterScreen.h"

using namespace std;

class clsMainScreen : protected clsScreen
{

private:

	enum enMainMenueOptions {
		eShowClientsList = 1, eAddNewClient = 2,
		eDeleteClient = 3, eUpdateClientInfo = 4,
		eFindClient = 5, eTransactions = 6,
		eManageUsers = 7, eLogRegScreen = 8, eExit = 9
	};

	static short _ReadMainMenuOption() {
		cout << setw(37) << left << "" << clsUtil::CYAN << "Choose what do you want to do? [1 to 9]: " << clsUtil::RESET;
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 9, "Enter Number between 1 to 9: ");
		return Choice;
	}

	static void _GoBackToMainMenu() {
		_PauseScreen("\t\t\t\t\tPress any key to go back to Main Menu...");
		ShowMainMenu();
	}

	static void _ShowAllClientsScreen() {
		clsClientListScreen::ShowAllClients();
	}

	static void _ShowAddNewClientsScreen() {
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _ShowDeleteClientScreen() {
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen() {
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen() {
		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsMenu() {
		clsTransactionMenueScreen::ShowTransactionMenue();
	}

	static void _ShowManageUsersMenu() {
		clsManageUsersScreen::ShowManageUsersScreen();
	}

	static void _ShowLogRegisterScreen() {
		clsLogRegisterScreen::ShowLoginRegisterScreen();
	}

	static void _Logout() {
		cout << clsUtil::GREEN << "\nYou have been logged out successfully. Goodbye!" << clsUtil::RESET;
	}

	static void _PerformMainMenuOption(enMainMenueOptions MainMenueOptions) {
		switch (MainMenueOptions) {
		case enMainMenueOptions::eShowClientsList: {
			_ClearScreen();
			_ShowAllClientsScreen();
			_GoBackToMainMenu();
			break;
		}
		case enMainMenueOptions::eAddNewClient:
			_ClearScreen();
			_ShowAddNewClientsScreen();
			_GoBackToMainMenu();
			break;

		case enMainMenueOptions::eDeleteClient:
			_ClearScreen();
			_ShowDeleteClientScreen();
			_GoBackToMainMenu();
			break;

		case enMainMenueOptions::eUpdateClientInfo:
			_ClearScreen();
			_ShowUpdateClientScreen();
			_GoBackToMainMenu();
			break;

		case enMainMenueOptions::eFindClient:
			_ClearScreen();
			_ShowFindClientScreen();
			_GoBackToMainMenu();
			break;

		case enMainMenueOptions::eTransactions:
			_ClearScreen();
			_ShowTransactionsMenu();
			_GoBackToMainMenu();
			break;

		case enMainMenueOptions::eManageUsers:
			_ClearScreen();
			_ShowManageUsersMenu();
			_GoBackToMainMenu();
			break;

		case enMainMenueOptions::eLogRegScreen:
			_ClearScreen();
			_ShowLogRegisterScreen();
			_GoBackToMainMenu();
			break;

		case enMainMenueOptions::eExit: {
			_ClearScreen();
			_Logout();
			break;
		}
		}
	}

public:

	static void ShowMainMenu() {
		_ClearScreen();
		_DrawScreenHeader("Main Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menu\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Client List\n";
		cout << setw(37) << left << "" << "\t[2] Add New Client\n";
		cout << setw(37) << left << "" << "\t[3] Delete Client\n";
		cout << setw(37) << left << "" << "\t[4] Update Client Info\n";
		cout << setw(37) << left << "" << "\t[5] Find Client\n";
		cout << setw(37) << left << "" << "\t[6] Transactions\n";
		cout << setw(37) << left << "" << "\t[7] Manage Users\n";
		cout << setw(37) << left << "" << "\t[8] Login/Register\n";
		cout << setw(37) << left << "" << "\t[9] Logout\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformMainMenuOption((enMainMenueOptions)_ReadMainMenuOption());
	}

};
