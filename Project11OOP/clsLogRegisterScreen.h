#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsUtility.h"

using namespace std;

class clsLogRegisterScreen : protected clsScreen
{
private:

public:
	static void ShowLoginRegisterScreen() {
		if (!CheckAccessRights(clsUser::enPermissions::pLoginRegister))
			return;

		vector <clsUser::stLoginRegisterRecord> vLoginRegister = clsUser::GetLoginRegisterList();
		
		string Title = "Login Register Screen";
		string SubTitle = "(" + to_string(vLoginRegister.size()) + ") Record(s)";

		_DrawScreenHeader(Title, SubTitle);

		cout << clsUtil::CYAN << "__________________________________________________________________________\n" << clsUtil::RESET;
		cout << clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(20) << "Date/Time"
			<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(20) << "UserName"
			<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(20) << "Password"
			<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(10) << "Permissions"
			<< clsUtil::CYAN << "|" << clsUtil::RESET << endl;
		cout << clsUtil::CYAN << "__________________________________________________________________________\n" << clsUtil::RESET;

		for (clsUser::stLoginRegisterRecord Record : vLoginRegister) {
			cout << clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(20) << Record.DateTime
				<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(20) << Record.UserName
				<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(20) << Record.Password
				<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(10) << Record.Permissions
				<< clsUtil::CYAN << "|" << clsUtil::RESET << endl;
		}

		cout << clsUtil::CYAN << "__________________________________________________________________________\n" << clsUtil::RESET;
		_PauseScreen("\n\t\t\t\tPress any key to go back to Main Menu...");
	}
};
