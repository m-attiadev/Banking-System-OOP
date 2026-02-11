#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUtility.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "clsBankClient.h"
#include "clsUser.h"
#include "Global.h"
#include <ctime>
#include "clsdate.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
	static bool _Login() {
		bool LoginFailed = false;
		string UserName, Password;
		short FailedLoginCount = 0;

		do {
			if (LoginFailed) {
				FailedLoginCount++;
				cout << clsUtil::RED << "\nInvalid UserName or Password. Try again..." << clsUtil::RESET << endl;
				cout << clsUtil::RED << "You have " << (3 - FailedLoginCount) << " attempts remaining." << clsUtil::RESET << endl;
			}

			if (FailedLoginCount == 3) {
				cout << clsUtil::RED << "\nYou have exceeded the maximum number of login attempts. Access denied!" << clsUtil::RESET << endl;
				return false;
			}

			cout << clsUtil::CYAN << "\n\t\t\t\tEnter UserName: " << clsUtil::RESET;
			UserName = clsInputValidate::ReadString();

			cout << clsUtil::CYAN << "\t\t\t\tEnter Password: " << clsUtil::RESET;
			Password = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(UserName, Password);
			LoginFailed = CurrentUser.IsEmpty();

		} while (LoginFailed);

		CurrentUser.RegesterLogIn();
		clsMainScreen::ShowMainMenu();

		return true;
	}

public:
	static bool ShowLoginScreen() {
		_ClearScreen();
		_DrawScreenHeader("Login Screen");
		return _Login();
	}
};
