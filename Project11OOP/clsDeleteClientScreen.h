#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUtility.h"
#include "clsBankClient.h"
using namespace std;

class clsDeleteClientScreen : protected clsScreen {
	
private:

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\n_________________________Client Card_________________________\n";
		cout << "\nFirst Name      : " << Client.getFirstName();
		cout << "\nLast Name       : " << Client.getLastName();
		cout << "\nFull Name       : " << Client.FullName();
		cout << "\nEmail           : " << Client.getEmail();
		cout << "\nPhone           : " << Client.getPhone();
		cout << "\nAccount Number  : " << Client.AccountNumber;
		cout << "\nPassword       : " << Client.PinCode;
		cout << "\nBalance : " << Client.AccountBalance;
		cout << "\n____________________________________________________________\n";
	}

public:
static void ShowDeleteClientScreen() {
if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
return;
		
_DrawScreenHeader("Delete Client Screen");

string AccountNumber = "";
AccountNumber = clsInputValidate::ReadString("Please Enter Account Number: ");

while (!clsBankClient::IsClientExist(AccountNumber)) {
cout << clsUtil::RED << "The account number was not found. Please enter a different account number." << clsUtil::RESET << endl;
AccountNumber = clsInputValidate::ReadString("Please Enter Account Number: ");
}

clsBankClient DeleteObj = clsBankClient::Find(AccountNumber);
_PrintClient(DeleteObj);

cout << clsUtil::YELLOW << "\nAre you sure you want to delete this account? (Y/N): " << clsUtil::RESET;
char Answer = 'n';
cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			DeleteObj.Delete();
			cout << "\nDone Deleted";
		}
		else
			cout << "\nAborted Deleting";
	}
};

