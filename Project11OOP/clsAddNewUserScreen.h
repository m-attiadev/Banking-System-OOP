#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUtility.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "clsBankClient.h"
#include "clsManageUsersScreen.h"
#include "clsUser.h"

using namespace std;

class clsAddNewUserScreen : protected clsScreen
{
private:
	static void _ReadUserInfo(clsUser& User) {
		
		cout << clsUtil::GREEN << "\n\t\t\t\tEnter Password? " << clsUtil::RESET;
		User.Password = clsInputValidate::ReadString();
		cout << clsUtil::GREEN << "\n\t\t\t\tEnter First Name? " << clsUtil::RESET;
		User.FirstName = clsInputValidate::ReadString();
		cout << clsUtil::GREEN << "\n\t\t\t\tEnter Last Name? " << clsUtil::RESET;
		User.LastName = clsInputValidate::ReadString();
		cout << clsUtil::GREEN << "\n\t\t\t\tEnter Email? " << clsUtil::RESET;
		User.Email = clsInputValidate::ReadString();
		cout << clsUtil::GREEN << "\n\t\t\t\tEnter Phone? " << clsUtil::RESET;
		User.Phone = clsInputValidate::ReadString();
		cout << clsUtil::GREEN << "\n\t\t\t\tEnter Permissions? " << clsUtil::RESET;
		User.Permissions = _ReadUserPermissions();
	}

	static int _ReadUserPermissions() {
		int Permissions = 0;
		char Answer = 'n';

		cout << clsUtil::RED << "\n\t\t\t\tDo You want to give full access? y/n " << clsUtil::RESET;
		cin >> Answer;

		if (tolower(Answer) == 'y') {
			return -1; // full access
		}

		cout << clsUtil::RED << "\n\t\t\t\tDo You want to give List Clients Permission? y/n " << clsUtil::RESET;
		
		cout << clsUtil::GREEN << "\n\t\t\t\t[1] List Clients? " << clsUtil::RESET;
		cin >> Answer;
		if (tolower(Answer) == 'y') Permissions |= clsUser::enPermissions::pAddNewClient;

		cout << clsUtil::GREEN << "\n\t\t\t\t[2] Add New Client? " << clsUtil::RESET;
		cin >> Answer;
		if (tolower(Answer) == 'y') Permissions |= clsUser::enPermissions::pAddNewClient;

		cout << clsUtil::GREEN << "\n\t\t\t\t[3] Delete Client? " << clsUtil::RESET;
		cin >> Answer;
		if (tolower(Answer) == 'y') Permissions |= clsUser::enPermissions::pDeleteClient;

		cout << clsUtil::GREEN << "\n\t\t\t\t[4] Update Client? " << clsUtil::RESET;
		cin >> Answer;
		if (tolower(Answer) == 'y') Permissions |= clsUser::enPermissions::pUpdateClient;

		cout << clsUtil::GREEN << "\n\t\t\t\t[5] Find Client? " << clsUtil::RESET;
		cin >> Answer;
		if (tolower(Answer) == 'y') Permissions |= clsUser::enPermissions::pFindClient;

		cout << clsUtil::GREEN << "\n\t\t\t\t[6] Transactions Menue? " << clsUtil::RESET;
		cin >> Answer;
		if (tolower(Answer) == 'y') Permissions |= clsUser::enPermissions::pTransactionsMenue;

		cout << clsUtil::GREEN << "\n\t\t\t\t[7] Manage Users? " << clsUtil::RESET;
		cin >> Answer;
		if (tolower(Answer) == 'y') Permissions |= clsUser::enPermissions::pManageUsers;

		return Permissions;
	}

	static void _PrintUser(clsUser User) {
		cout << "\nUser Name: " << User.UserName;
		cout << "\nPassword: " << User.Password;
		cout << "\nFirst Name: " << User.FirstName;
		cout << "\nLast Name: " << User.LastName;
		cout << "\nEmail: " << User.Email;
		cout << "\nPhone: " << User.Phone;
		cout << "\nPermissions: " << User.Permissions;
	}

public:
	static void ShowAddNewUserScreen() {
		system("cls");
		_DrawScreenHeader("Add New User Screen");
		
		string UserName = "";
		cout << clsUtil::GREEN << "\n\t\t\t\tEnter User Name? " << clsUtil::RESET;
		UserName = clsInputValidate::ReadString();
		while (clsUser::IsUserExists(UserName))
		{
			cout << "\nUserName Is Already Used, Choose another one: ";
			UserName = clsInputValidate::ReadString();
		}
		clsUser NewUser = clsUser::GetAddNewUserObject(UserName);
		_ReadUserInfo(NewUser);

		clsUser::enSaveResults SaveResult;

		SaveResult = NewUser.Save();

		switch (SaveResult)
		{
		case  clsUser::enSaveResults::svSucceeded:
		{
			cout << "\nUser Addeded Successfully :-)\n";
			_PrintUser(NewUser);
			break;
		}
		case clsUser::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nError User was not saved because it's Empty";
			break;

		}
		case clsUser::enSaveResults::svFaildUserNameExists:
		{
			cout << "\nError User was not saved because UserName is used!\n";
			break;

		}
		}
	}

};
