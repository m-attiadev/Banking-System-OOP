#pragma once
#include <iostream>

#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
using namespace std;

class clsWithdrawScreen :protected clsScreen {
	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber;
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << fixed << setprecision(2) << Client.AccountBalance;
		cout << "\n___________________\n";

	}
public:

	static void ShowWithdrawScreen()
	{
		_DrawScreenHeader("Withdraw Screen");

		string AccountNumber = clsInputValidate::ReadString("\n\t\t\t\t\tPlease enter account number: ");
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\n\t\t\t\t\tAccount number not found. Please try again.";
			AccountNumber = clsInputValidate::ReadString("\n\t\t\t\t\tPlease enter account number: ");
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClient(Client);

		cout << "\nPlease enter amount to Withdraw: ";
		double Amount = clsInputValidate::ReadDblNumber();
		cout << "\nAre you sure you want to perform this transaction? [y or n] ";
		char Answer = 'n';
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			while (Amount > Client.AccountBalance || Amount <= 0) {
				cout << "Insufficient funds. Please enter a valid amount to withdraw: ";
				Amount = clsInputValidate::ReadDblNumber();
			}
			Client.WithDraw(Amount);
			cout << "\nAmount Withdraw Successfully.\n";
			cout << "\nNew Balance Is: " << fixed << setprecision(2)  << Client.AccountBalance;

		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}
	}
};
