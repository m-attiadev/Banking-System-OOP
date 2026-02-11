#pragma once
#include <iomanip>
#include <string>
#include <iostream>
#include "clsUtility.h"
#include "Global.h"

using namespace std;

class clsScreen
{
protected:

	static void _DrawScreenHeader(string Title, string SubTitle = "") {
		cout << clsUtil::YELLOW
			<< "\t\t\t\t________________________________________________________" << clsUtil::RESET;
		cout << clsUtil::RED
			<< "\n\n\t\t\t\t\t\t\t" << Title << clsUtil::RESET;

		cout << clsUtil::YELLOW
			<< "\n\t\t\t\tUser: " << CurrentUser.UserName << clsUtil::RESET << endl;

		if (SubTitle != "")
			cout << "\n\t\t\t\t\t\t\t" << clsUtil::BLUE << SubTitle << clsUtil::RESET;
		
		cout << clsUtil::YELLOW
			<< "\n\t\t\t\t________________________________________________________\n" << clsUtil::RESET;
	}

	static bool CheckAccessRights(clsUser::enPermissions RequiredPermissions) {
		if (CurrentUser.Permissions == clsUser::eAll || (CurrentUser.Permissions & RequiredPermissions) == RequiredPermissions)
			return true;
		
		cout << clsUtil::RED << "\nAccess Denied! You don't have the required permissions to perform this action." << clsUtil::RESET << endl;
		return false;
	}

	static void _PauseScreen(string Message = "Press any key to continue...") {
		cout << clsUtil::GREEN << "\n" << Message << clsUtil::RESET << endl;
		system("pause>0");
	}

	static void _ClearScreen() {
		system("cls");
	}

};
