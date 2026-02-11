#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUtility.h"
#include "clsBankClient.h"
using namespace std;

class clsUpdateClientScreen : protected clsScreen {
private:
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

	static void _ReadClientInfo(clsBankClient& Client) {
		Client.FirstName = clsInputValidate::ReadString("Please enter first name: ");

		Client.LastName = clsInputValidate::ReadString("Please enter last name: ");

		Client.Email = clsInputValidate::ReadString("Please enter email: ");

		Client.Phone = clsInputValidate::ReadString("Please enter phone: ");

		Client.AccountNumber = clsInputValidate::ReadString("Please enter account number: ");

		Client.PinCode = clsInputValidate::ReadString("Please enter pin code: ");

		cout << "Please enter account balance: ";
		Client.AccountBalance = clsInputValidate::ReadFloatNumber();
	}
public:

static void ShowUpdateClientScreen() {
if (!CheckAccessRights(clsUser::enPermissions::pUpdateClient))
return;

_DrawScreenHeader("Update Client Screen");

string AccountNumber = "";
AccountNumber = clsInputValidate::ReadString("Please enter account number: ");

while (!clsBankClient::IsClientExist(AccountNumber)) {
cout << clsUtil::RED << "The account number was not found. Please enter a valid account number." << clsUtil::RESET << endl;
AccountNumber = clsInputValidate::ReadString("Please enter account number: ");
}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		cout << "Update Client Info:\n";
		cout << "------------------------------\n";

		_ReadClientInfo(Client);

		clsBankClient::enSaveResults SaveResult = Client.Save();

		switch (SaveResult)
		{
		case clsBankClient::enSaveResults::svFailedEmptyObject:
			cout << "Error: Failed to save client data. The client object is empty.\n";
			break;
		case clsBankClient::enSaveResults::svSucceeded:
			cout << "Client data saved successfully.\n";
			_PrintClient(Client);
			break;
		default:
			break;
		}

	}
};
