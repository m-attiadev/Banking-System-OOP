#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUtility.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsersScreen : protected clsScreen
{
private:

	enum enManageUsersOptions {
		eListUsers = 1, eAddNewUsers = 2,
		eDeleteUsers = 3, eUpdateUsersInfo = 4,
		eFindUsers = 5, eMainMenu = 6
	};

	static short _ReadManageUsersOption() {
		cout << setw(37) << left << "" << clsUtil::CYAN << "Choose what do you want to do? [1 to 6]: " << clsUtil::RESET;
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6: ");
		return Choice;
	}

	static void _GoBackToManageUsersMenu() {
		_PauseScreen("\t\t\t\t\tPress any key to go back to Manage Users Menu...");
		ShowManageUsersScreen();
	}

	static void _ShowUsersListScreen() {
		ListUsersScreen::ShowAllUsers();
	}	

	static void _ShowAddNewUserScreen() {
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteUserScreen() {
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserScreen() {
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}
	
	static void _ShowFindUserScreen() {
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _PerformManageUsersOptions(enManageUsersOptions enOption) {
	
		if (enOption == clsManageUsersScreen::eMainMenu)
			return;
		
		_ClearScreen();
		switch (enOption)
		{
		case enManageUsersOptions::eListUsers:
		{
			_ShowUsersListScreen();
			_GoBackToManageUsersMenu();
			break;
		}
		case enManageUsersOptions::eAddNewUsers:
		{
			_ShowAddNewUserScreen();
			_GoBackToManageUsersMenu();
			break;
		}
		case enManageUsersOptions::eDeleteUsers:
		{
			_ShowDeleteUserScreen();
			_GoBackToManageUsersMenu();
			break;
		}
		case enManageUsersOptions::eUpdateUsersInfo:
		{
			_ShowUpdateUserScreen();
			_GoBackToManageUsersMenu();
			break;
		}
		case enManageUsersOptions::eFindUsers:
		{
			_ShowFindUserScreen();
			_GoBackToManageUsersMenu();
			break;
		}
		}
	}

public:
	static void ShowManageUsersScreen() {
		_ClearScreen();
		_DrawScreenHeader("Manage Users Screen");
		
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t\tManage Users\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Users\n";
		cout << setw(37) << left << "" << "\t[2] Add New User\n";
		cout << setw(37) << left << "" << "\t[3] Delete User\n";
		cout << setw(37) << left << "" << "\t[4] Update User Info\n";
		cout << setw(37) << left << "" << "\t[5] Find User\n";
		cout << setw(37) << left << "" << "\t[6] Main Menu\n";
		cout << setw(37) << left << "" << "===========================================\n";
		
		_PerformManageUsersOptions((enManageUsersOptions)_ReadManageUsersOption());
	}
};
