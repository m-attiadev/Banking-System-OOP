#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include <iomanip>
using namespace std;

class clsBankClient : public clsPerson
{
private:


	enum enMode { EmptyMode = 0, UpdateMode =1, AddNewMode =2};
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkForDelete = false;

	// the static methode call sshould be static 
	static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#") {
		vector <string> vClientData;
		vClientData = clsString::Split(Line, Seperator);
		return clsBankClient(
			clsBankClient::enMode::UpdateMode,
			vClientData[0],
			vClientData[1],
			vClientData[2],
			vClientData[3],
			vClientData[4], 
			vClientData[5],
			stof(vClientData[6])
		);
	}

	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(
			clsBankClient::enMode::EmptyMode,
			"",
			"",
			"",
			"",
			"",
			"",
			0
		);
	}

	static vector <clsBankClient> _LoadClientsDataFromFile(string FileName) {
		vector <clsBankClient> vClients;
		fstream MyFile;
		MyFile.open(FileName, ios::in); // read mode
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return vClients;
	}

	static string _ConvertClientObjectToLine(clsBankClient Client) {
		string Line = "";
		Line += Client.getFirstName() + "#//#";
		Line += Client.getLastName() + "#//#";
		Line += Client.getEmail() + "#//#";
		Line += Client.getPhone() + "#//#";
		Line += Client.AccountNumber + "#//#";
		Line += Client.PinCode + "#//#";
		Line += to_string(Client.AccountBalance);
		return Line;
	}

	void _SaveClientsDataToFile(vector <clsBankClient> vClients) {
		
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out); // write mode

		string DateLine;

		if (MyFile.is_open())
		{
			for (clsBankClient Client : vClients) {
				if (Client._MarkForDelete == false) // لو مش مارك فور دليت بس احفظه
				{
					DateLine = _ConvertClientObjectToLine(Client);
					MyFile << DateLine << endl;
				}
				
			}
			MyFile.close();
		}
	}

	void _Update() {
		vector <clsBankClient> _vClients = _LoadClientsDataFromFile("Clients.txt");

		for (clsBankClient& Client : _vClients) {
			if (Client.AccountNumber == AccountNumber)
			{
				Client = *this;
				break;
			}
		}
		_SaveClientsDataToFile(_vClients);

	}

	void _AddDataLineToFile(string DataLine) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::app); // append mode
		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;
			MyFile.close();
		}
	}

	void _AddNew() {
		_AddDataLineToFile(_ConvertClientObjectToLine(*this)); // this ببعتله الاوبجكت الي موقف عليه نفسه

	}


public:

	enum enSaveResults { svFailedEmptyObject = 0, svSucceeded = 1 , svFailedAccountNumberExists = 2};

	clsBankClient(enMode Mode, string FirstName , string LastName ,
		string Email, string Phone, string AccountNumber, 
		string PinCode, float AccountBalance):
		clsPerson(FirstName, LastName, Email, Phone) 
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	void SetAccountNumber(string NewAccountNumber)
	{
		_AccountNumber = NewAccountNumber;
	}
	
	string GetAccountNumber()
	{
		return _AccountNumber;
	}
	__declspec(property(get = GetAccountNumber, put = SetAccountNumber)) string AccountNumber;

	void SetAccountBalance(double NewBalance)
	{
		_AccountBalance = NewBalance;
	}
	double GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;
	
	void setPinCode(string NewPin)
	{
		_PinCode = NewPin;
	}
	string GetPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = setPinCode)) string PinCode;
	

	// رح اليغيها واغلي الطباعه في كلاسات ال يو اي
	/*void Print()
	{
		cout << "\n_________________________Client Card_________________________\n";
		cout << "\nFirst Name      : " << getFirstName();
		cout << "\nLast Name       : " << getLastName();
		cout << "\nFull Name       : " << FullName();
		cout << "\nEmail           : " << getEmail();
		cout << "\nPhone           : " << getPhone();
		cout << "\nAccount Number  : " << _AccountNumber;
		cout << "\nPassword       : " << _PinCode;
		cout << "\nBalance : " << _AccountBalance;
		cout << "\n____________________________________________________________\n";
	}*/
	
	static clsBankClient Find(string AccountNumber) {

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in); // read mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber == AccountNumber)
				{
					MyFile.close(); // This is very iportant to close the file after using it 
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode) {

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in); // read mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close(); // This is very iportant to close the file after using it 
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}


	static bool IsClientExist(string AccountNumber) {
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		return (!Client1.IsEmpty());
	}
	
	static clsBankClient GetAddNewClientObject(string AccountNumber) {
		return clsBankClient(
			clsBankClient::enMode::AddNewMode,
			"",
			"",
			"",
			"",
			AccountNumber,
			"",
			0
		);
	}

	static vector<clsBankClient> GetClientsList() { // عملتها ستاتيك عشان اقدر اوصلها من غير ما اعمل اوبجكت
		return _LoadClientsDataFromFile("Clients.txt");
	}

	static double GetTotalBalances() {
		vector <clsBankClient> vClients = _LoadClientsDataFromFile("Clients.txt");
		double TotalBalances = 0;
		for (clsBankClient Client : vClients) {
			TotalBalances += Client.AccountBalance;
		}
		return TotalBalances;
	}

	enSaveResults Save() {
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			return enSaveResults::svFailedEmptyObject;
		}
		case clsBankClient::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;
			break;
		}
		case clsBankClient::AddNewMode:
		{
			// Check if Account Number already exists
			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResults::svFailedAccountNumberExists;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode; // لازم اغير المود عشان لو ضفته ثاني يروح يعدل مش يضيف
				return enSaveResults::svSucceeded;
			}
		}
		default:

			break;
		}
	}

	void Deposit(double Amount) {
		_AccountBalance += Amount;
		Save();
	}

	void WithDraw(double Amount) {
		_AccountBalance -= Amount;
		Save();
	}

	 void Transfer(double Amount, clsBankClient ClientSender, clsBankClient ClientRecevier) {
		ClientSender.WithDraw(Amount);
		ClientRecevier.Deposit(Amount);
		Save();
	}

	bool Delete() {
		vector <clsBankClient> vClients = _LoadClientsDataFromFile("Clients.txt");
		for (clsBankClient &Client : vClients) {

			if (Client.AccountNumber == _AccountNumber) {
				Client._MarkForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);
		*this = _GetEmptyClientObject();
		return true;
	}
	

	bool IsEmpty()
	{
		return _Mode == EmptyMode;
	}
};
