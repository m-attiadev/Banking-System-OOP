#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsFindUserScreen :protected clsScreen
{

private:
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUserName    : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";

    }

public:

static void ShowFindUserScreen() {
    _DrawScreenHeader("Find User Screen");

    string UserName;
    cout << clsUtil::CYAN << "\nPlease Enter UserName: " << clsUtil::RESET;
    UserName = clsInputValidate::ReadString();
        
    while (!clsUser::IsUserExists(UserName)) {
        cout << clsUtil::RED << "\nUser not found. Please enter a different username: " << clsUtil::RESET;
        UserName = clsInputValidate::ReadString();
    }

    clsUser User = clsUser::Find(UserName);

    if (!User.IsEmpty()) {
        cout << clsUtil::GREEN << "\nUser Found!" << clsUtil::RESET << endl;
        } else {
            cout << clsUtil::RED << "\nUser Not Found!" << clsUtil::RESET << endl;
            return;
        }

        _PrintUser(User);
    }
};

