#pragma once
#include "clsScreen.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include "clsBankClient.h"
#include "clsUtility.h"
#include "clsUser.h"
#include "Global.h"


using namespace std;

class clsClientListScreen : protected clsScreen {
private:


public:

	

	static void ShowAllClients() {
		if (!CheckAccessRights(clsUser::enPermissions::pListClients))
			return;
		
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		string Title = "Clients List Screen";
		string SubTitle = "(" + to_string(vClients.size()) + ") Client(s)";

		_DrawScreenHeader(Title, SubTitle);

		cout << clsUtil::CYAN << "__________________________________________________________________________________________________________________\n" << clsUtil::RESET;

		cout << clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(15) << "Account Number"
			<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(20) << "Client Name"
			<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(12) << "Phone"
			<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(25) << "Email"
			<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(10) << "Pin Code"
			<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(14) << "Balance"
			<< clsUtil::CYAN << "|" << clsUtil::RESET << endl;

		cout << clsUtil::CYAN << "__________________________________________________________________________________________________________________\n" << clsUtil::RESET;

		for (clsBankClient Client : vClients) {
			cout << clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(15) << Client.AccountNumber
				<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(20) << (Client.FirstName + " " + Client.LastName)
				<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(12) << Client.Phone
				<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(25) << Client.Email
				<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(10) << Client.PinCode
				<< clsUtil::CYAN << "| " << clsUtil::GREEN << left << setw(12) << fixed << setprecision(2) << Client.AccountBalance << left << setw(2) << "$" << clsUtil::RESET
				<< clsUtil::CYAN << "|" << clsUtil::RESET << endl;
		}

		cout << clsUtil::CYAN << "__________________________________________________________________________________________________________________\n" << clsUtil::RESET;
	}

};