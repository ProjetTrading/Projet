/*Compiler: g++ main.cpp ./src/Msg.cpp*/
#include <iostream>
#include <string>
#include <unistd.h>
#include "include/Msg.h"

using namespace std;


int main()
{
	/* test sur un msg new order */
	string msg="8=FIX.4.1|9=0235|35=D|34=10|43=N|49=VENDOR|50=CUSTOMER|56=BROKER|52=19980930-09:25:58|1=XQCCFUND|11=10|21=1|55=EK|48=277461109|22=1|54=1|38=10000|40=2|44=76.750000|10=165|";
	cout << "Test du message:" << msg << endl;
    /* creation de classe statique */
    Msg testMsg(msg);
    testMsg.displayTags();
    
    return 0;
}
