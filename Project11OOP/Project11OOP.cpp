#include <iostream>
#include <string>
#include <iomanip>

#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsUtility.h"
#include "clsMainScreen.h"
#include <vector>
#include "clsClientListScreen.h"
#include "clsLoginScreen.h"

using namespace std;


int main()
{
    while (true)
    {
        CurrentUser = clsUser::Find("", "");

        if (!clsLoginScreen::ShowLoginScreen()) {
            break;
        }
    }
  
    return 0;
}