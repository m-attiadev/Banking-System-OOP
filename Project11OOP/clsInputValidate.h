#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include "clsDate.h"
using namespace std;
class clsInputValidate
{
public:
	static bool IsNumberBetween(int Number, int From, int To) {
		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(double Number, double From, double To) {
		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(short Number, short From, short To) {
		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(float Number, float From, float To) {
		return (Number >= From && Number <= To);
	}

	static short ReadShortNumber(string ErrorMessage = "Invalid Input, Enter agian\n") {
		short Number = 0;
		while (!(cin >> Number)) {
			cin.clear(); // The bais This Function Perposes clear Flag in The Buffer
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // The Main Function Is a Clear Full Buffer And \n 
			cout << ErrorMessage;
		}
		return Number;
	}

	static int ReadIntNumber(string ErrorMessage = "Invalid Input, Enter agian\n") {
		int Number = 0;
		while (!(cin >> Number)) {
			cin.clear(); // The bais This Function Perposes clear Flag in The Buffer
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // The Main Function Is a Clear Full Buffer And \n 
			cout << ErrorMessage;
		}
		return Number;
	}

	static float ReadFloatNumber(string ErrorMessage = "Invalid Input, Enter agian\n") {
		float Number = 0;
		while (!(cin >> Number)) {
			cin.clear(); // The bais This Function Perposes clear Flag in The Buffer
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // The Main Function Is a Clear Full Buffer And \n 
			cout << ErrorMessage;
		}
		return Number;
	}
	
	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{

		if (clsDate::IsDate1AfterDate2(Date, To))
		{
			clsDate Temp = From;
			From = To;
			To = Temp;
		}
		return ((clsDate::IsDate1AfterDate2(Date, From)) || (clsDate::IsDate1EqualToDate2(Date, From)))
			&&
			((clsDate::IsDate1BeforeDate2(Date, To)) || (clsDate::IsDate1EqualToDate2(Date, To)));
	}

	static double ReadDblNumber(string ErrorMessage = "Invalid Input, Enter agian\n")
	{
		double Number = 0;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << ErrorMessage;
		}

		return Number;
	}

	static int ReadShortNumberBetween(short From, short To, string ErrorMessage) {
		short Number = ReadIntNumber();

		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadIntNumber();
		}
		return Number;
	}
	
	static int ReadIntNumberBetween(int From, int To, string ErrorMessage) {
		int Number = ReadIntNumber();

		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadIntNumber();
		}
		return Number;
	}

	static double ReadDblNumberBetween(double From, double To, string ErrorMessage) {
		double Number = ReadDblNumber();

		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadIntNumber();
		}
		return Number;
	}
	static string ReadString() {
		string InputString;
		getline(cin >> ws, InputString);
		return InputString;
	}

	static string ReadString(string Message) {
		string InputString;
		cout << Message;
		getline(cin >> ws, InputString);
		return InputString;
	}

	static bool IsValidDate(clsDate Date) {
		return clsDate::IsValidDate(Date);
	}

};