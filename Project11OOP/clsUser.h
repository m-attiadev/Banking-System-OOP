#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUtility.h"
#include "clsPerson.h"
#include <fstream>
#include "clsDate.h"
#include "Global.h"


using namespace std;

class clsUser : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode, AddNewMode };
	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkedForDelete = false;


	string _PrepareUserLoginLogLine(string Separator = "#//#") {
		string LogLine = "";
		LogLine += clsDate().GetSystemDateTimeString() + Separator;
		LogLine += this->UserName + Separator;
		LogLine += this->Password + Separator;
		LogLine += to_string(this->Permissions);
		return LogLine;
	}
	struct stLoginRegisterRecord;

	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;


		vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
		LoginRegisterRecord.Password = LoginRegisterDataLine[2];
		LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

		return LoginRegisterRecord;

	}



	static clsUser _ConvertLineToRecordUser(string Line) {
		vector<string> vUserData = clsString::Split(Line, "#//#");
		return clsUser(clsUser::enMode::UpdateMode, vUserData[0],
			vUserData[1], vUserData[2], vUserData[3],
			vUserData[4], vUserData[5], stoi(vUserData[6]));
	}
	static vector <clsUser> _LoadUsersDataFromFile(string FileName) {
		vector <clsUser> vUsers;
		fstream MyFile;
		MyFile.open(FileName, ios::in); // read mode
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line)) {
				vUsers.push_back(_ConvertLineToRecordUser(Line));
			}
			MyFile.close();
		}
		return vUsers;
	}

	static string _ConvertUserObjectToLine(clsUser& User) {
		string Line = "";
		Line += User.FirstName + "#//#";
		Line += User.LastName + "#//#";
		Line += User.Email + "#//#";
		Line += User.Phone + "#//#";
		Line += User.UserName + "#//#";
		Line += User.Password + "#//#";
		Line += to_string(User.Permissions);
		return Line;
	}

	static void _SaveUsersDataToFile(vector <clsUser> vUsers) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::out); // write mode
		string DateLine;
		if (MyFile.is_open())
		{
			for (clsUser User : vUsers) {
				if (User._MarkedForDelete == false) // ?? ?? ???? ??? ???? ?? ?????
				{
					DateLine = _ConvertUserObjectToLine(User);
					MyFile << DateLine << endl;
				}
			}
			MyFile.close();
		}
	}

	void _AddDataLineToFile(string DataLine) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::app); // append mode
		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;
			MyFile.close();
		}
	}

	void _Update() {
		vector <clsUser> _vUser = _LoadUsersDataFromFile("Users.txt");

		for (clsUser& User : _vUser) {
			if (User.UserName == _UserName)
			{
				User = *this;
				break;
			}
		}
		_SaveUsersDataToFile(_vUser);
	}

	void _AddNew() {
		_AddDataLineToFile(_ConvertUserObjectToLine(*this)); // this ?????? ???????? ??? ???? ???? ????
	}



	static clsUser _GetEmptyUserObject() {
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

public:
	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClient = 8, pFindClient = 16, pTransactionsMenue = 32, pManageUsers = 64, pLoginRegister = 128
	};

	struct stLoginRegisterRecord
	{
		string DateTime;
		string UserName;
		string Password;
		int Permissions;

	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email,
		string Phone, string UserName, string Password, int Permissions) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	bool IsEmpty() {
		return _Mode == EmptyMode;
	}

	bool IsMarkedForDelete() {
		return _MarkedForDelete;
	}

	static bool IsUserExists(string UserName) {
		vector <clsUser> vUsers = _LoadUsersDataFromFile("Users.txt");
		for (clsUser User : vUsers) {
			if (User.UserName == UserName)
			{
				return true;
			}
		}
		return false;
	}


	string getUserName() {
		return _UserName;
	}
	void setUserName(string UserName) {
		_UserName = UserName;
	}
	__declspec(property(get = getUserName, put = setUserName)) string UserName;

	string getPassword() {
		return _Password;
	}
	void setPassword(string Password) {
		_Password = Password;
	}
	__declspec(property(get = getPassword, put = setPassword)) string Password;

	void setPermissions(int Permissions) {
		_Permissions = Permissions;
	}
	int getPermissions() {
		return _Permissions;
	}
	__declspec(property(get = getPermissions, put = setPermissions)) int Permissions;


	static clsUser Find(string UserName) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLineToRecordUser(Line);
				if (User.UserName == UserName)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string Password) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLineToRecordUser(Line);
				if (User.UserName == UserName && User.Password == Password)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	enum enSaveResults {
		svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserNameExists = 2
	};

	enSaveResults Save() {

		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			if (IsEmpty())
				return enSaveResults::svFaildEmptyObject;
			break;
		}
		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;
		}
		case enMode::AddNewMode:
		{
			if (clsUser::IsUserExists(_UserName))
			{
				return enSaveResults::svFaildUserNameExists;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
		}
		}
		return enSaveResults::svFaildEmptyObject;
	};


	bool Delete() {
		vector <clsUser> vUsers = _LoadUsersDataFromFile("Users.txt");
		for (clsUser& User : vUsers) {
			if (User.UserName == _UserName) {
				User._MarkedForDelete = true;
				break;
			}
		}
		_SaveUsersDataToFile(vUsers);
		*this = _GetEmptyUserObject();
		return true;
	}

	static clsUser GetAddNewUserObject(string UserName) {
		return clsUser(
			clsUser::enMode::AddNewMode,
			"",
			"",
			"",
			"",
			UserName,
			"",
			0
		);
	}

	static vector<clsUser> GetUsersList() {
		return _LoadUsersDataFromFile("Users.txt");
	}



	bool CheckAccessPermission(enPermissions Permission) {
		if (this->Permissions == enPermissions::eAll)
			return true;
		if ((Permission & this->Permissions) == Permission)
			return true;
		else
			return false;
	}



	void RegesterLogIn() {

		fstream MyFile;
		string LogLine = _PrepareUserLoginLogLine();
		MyFile.open("LoginRegister.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << LogLine << endl;
			MyFile.close();
		}
	}

	static  vector <stLoginRegisterRecord> GetLoginRegisterList()
	{
		vector <stLoginRegisterRecord> vLoginRegisterRecord;

		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;

			stLoginRegisterRecord LoginRegisterRecord;

			while (getline(MyFile, Line))
			{

				LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);

				vLoginRegisterRecord.push_back(LoginRegisterRecord);

			}

			MyFile.close();

		}

		return vLoginRegisterRecord;

	}
};
