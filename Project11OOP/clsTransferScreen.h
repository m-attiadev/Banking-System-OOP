#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUtility.h"
#include "clsBankClient.h"
using namespace std;

class clsTransferScreen : protected clsScreen {
	static void _PrintClientSender(clsBankClient Client)
	{
		cout << "\nClient Sender Card:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.AccountNumber;
		cout << "\nBalance     : " << fixed << setprecision(2) << Client.AccountBalance;
		cout << "\n___________________\n";

	}
	static void _PrintClientRecevier(clsBankClient Client)
	{
		cout << "\nClient Recevier Card:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.AccountNumber;
		cout << "\n___________________\n";

	}
public:
	static void ShowTransferScreen() {

		_DrawScreenHeader("Transfer Screen");
		string AccountNumberSender = clsInputValidate::ReadString("\n\t\t\t\t\tPlease enter account number Sender: ");

		
		while (!clsBankClient::IsClientExist(AccountNumberSender))
		{
			cout << "\n\t\t\t\t\tAccount number Sender not found. Please try again.";
			AccountNumberSender = clsInputValidate::ReadString("\n\t\t\t\t\tPlease enter account number Sender: ");
		}
	
		string AccountNumberReceiver = clsInputValidate::ReadString("\n\t\t\t\t\tPlease enter account number Receiver: ");
		
		while (!clsBankClient::IsClientExist(AccountNumberReceiver) && AccountNumberSender == AccountNumberReceiver)
		{
			cout << "\n\t\t\t\t\tAccount number not found . Please try again.";
			AccountNumberReceiver = clsInputValidate::ReadString("\n\t\t\t\t\tPlease enter account number: ");
		}

		clsBankClient ClientSender = clsBankClient::Find(AccountNumberSender);
		clsBankClient ClientRecevier = clsBankClient::Find(AccountNumberReceiver);

		_PrintClientSender(ClientSender);
		_PrintClientRecevier(ClientRecevier);

		cout << "\nPlease enter amount to Reciver: ";
		double Amount = clsInputValidate::ReadDblNumber();

		cout << "\nAre you sure you want to perform this transaction? [y or n] ";
		char Answer = 'n';
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{

			ClientSender.WithDraw(Amount);
			ClientRecevier.Deposit(Amount);
			//ClientSender.Transfer(Amount, ClientSender, ClientRecevier);
			cout << "\n Transfer Successfully.\n";
			cout << "\nNew Balance Is: " << fixed << setprecision(2) << ClientSender.AccountBalance;
		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}
	}
};
