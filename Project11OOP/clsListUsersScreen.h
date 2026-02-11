#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsPerson.h"
#include <iomanip>

using namespace std;

class ListUsersScreen : protected clsScreen
{
private:
	static void _PrintUserRecord(clsUser User) {
		cout << setw(15) << left << User.UserName;
		cout << setw(20) << left << User.FullName();
		cout << setw(30) << left << User.Email;
		cout << setw(15) << left << User.Phone;
		cout << setw(10) << left << User.Permissions;
		cout << endl;
	}
public:
	static void ShowAllUsers() {
		vector <clsUser> vUsers = clsUser::GetUsersList();

		string Title = "Users List Screen";
		string SubTitle = "(" + to_string(vUsers.size()) + ") User(s)";

		_DrawScreenHeader(Title, SubTitle);

		cout << clsUtil::CYAN << "__________________________________________________________________________________________________________________\n" << clsUtil::RESET;


		// لاحظ بنطبع الفاصل الملون لوحده وبعدين الـ setw للنص بس
		cout << clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(15) << "Account Number"
			<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(20) << "User Name"
			<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(12) << "Phone"
			<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(25) << "Email"
			<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(10) << "Password"
			<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(14) << "Permissions"
			<< clsUtil::CYAN << "|" << clsUtil::RESET << endl;

		cout << clsUtil::CYAN << "__________________________________________________________________________________________________________________\n" << clsUtil::RESET;

		for (clsUser User : vUsers	) {
			cout << clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(15) << User.UserName
				<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(20) << (User.FirstName + " " + User.LastName)
				<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(12) << User.Phone
				<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(25) << User.Email
				<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(10) << User.Password
				<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(14) << User.Permissions
				<< clsUtil::CYAN << "|" << clsUtil::RESET << endl;
		}

		cout << clsUtil::CYAN << "__________________________________________________________________________________________________________________\n" << clsUtil::RESET;
	}
};
