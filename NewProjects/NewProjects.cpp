#include "clsUtil.h"
#include<iostream>
#include<vector>
#include"clsString.h"
#include"clsDate.h"
#include"clsBankClient.h"
using namespace std;

int main()
{
    clsBankClient Client1 = clsBankClient::Find("A101");
    Client1.Print();

    clsBankClient Client2 = clsBankClient::Find("A105");
    Client2.Print();
}
