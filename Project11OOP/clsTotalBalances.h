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
using namespace std;

class clsTotalBalances : protected clsScreen {

public:

	static void ShowTotalBalances() {

		_DrawScreenHeader("Total Balances Screen");
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();


		cout << "\n\t\t\t\t" << clsUtil::CYAN << "Total Balances List (" << vClients.size() << ") Client(s)" << clsUtil::RESET << "\n";
		cout << clsUtil::CYAN << "__________________________________________________________________________________________\n" << clsUtil::RESET;

		cout << clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(20) << "Account Number"
			<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(35) << "Client Name"
			<< clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(19) << "Balance"
			<< clsUtil::CYAN << "|" << clsUtil::RESET << endl;

		cout << clsUtil::CYAN << "__________________________________________________________________________________________\n" << clsUtil::RESET;

		if (vClients.size() == 0) {
			cout << "\t\t\t\tNo clients found in the system.\n";
		}
		else {
			for (clsBankClient Client : vClients) {

				cout << clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(20) << Client.AccountNumber;
				cout << clsUtil::CYAN << "| " << clsUtil::RESET << left << setw(35) << Client.FullName();
				cout << clsUtil::CYAN << "| " << clsUtil::RESET << clsUtil::GREEN << left << setw(14) << fixed << setprecision(2) << Client.AccountBalance << left << setw(3) << "$" << clsUtil::RESET;
				cout << clsUtil::CYAN << "|" << clsUtil::RESET << endl;
			}

			cout << clsUtil::CYAN << "__________________________________________________________________________________________\n" << clsUtil::RESET;
			double TotalBalances = clsBankClient::GetTotalBalances();


			cout << "\n\t\t\t\tTotal Balances = " << clsUtil::GREEN << fixed << setprecision(2) << TotalBalances << clsUtil::RESET << endl;

			/*cout << "\t\t\t\t( " << to_string(TotalBalances) << " )" << endl;*/
		}
	}

};