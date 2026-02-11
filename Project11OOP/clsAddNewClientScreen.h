#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUtility.h"
#include "clsBankClient.h"
using namespace std;

class clsAddNewClientScreen : protected clsScreen {
private:
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
static void ShowAddNewClientScreen() {
if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
return;

_DrawScreenHeader("Add New Client Screen");

string AccountNumber = "";
AccountNumber = clsInputValidate::ReadString("Please Enter Account Number: ");

while (clsBankClient::IsClientExist(AccountNumber)) {
cout << clsUtil::RED << "The account number already exists, please enter a different account number." << clsUtil::RESET << endl;
AccountNumber = clsInputValidate::ReadString("Please Enter Account Number: ");
}

clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

_ReadClientInfo(NewClient);

clsBankClient::enSaveResults SaveResult;
SaveResult = NewClient.Save();

switch(SaveResult)
{
case clsBankClient::enSaveResults::svFailedEmptyObject: 
{
cout << clsUtil::RED << "Error: Failed to save client data. The client object is empty." << clsUtil::RESET << endl;
break;
}
case clsBankClient::enSaveResults::svSucceeded:
{
cout << clsUtil::GREEN << "Client data saved successfully." << clsUtil::RESET << endl;
_PrintClient(NewClient);
break;
			}

			default:
				break;
		}
	
}
};