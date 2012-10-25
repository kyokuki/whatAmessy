#include <iostream>
#include "string.h"
using namespace std;

int main(int argc, char **argv)
{
    String string1;
    string1 = "string1";
    String string2("string2");
    String string3 = String(string2); 
    String string4;
    string4 = string3;
    String string5("string5");
    String string6("string6");
    
    cout << "string5 > string6 : " << (string5 > string6) << endl;
    cout <<  "string5[1] : " << string5[1] << endl;
    string5[1] = 'a';
    cout << string5 << endl;
    
    cout << "num_strings = " <<String::HowMany() << endl ;
    cout << " string + string : " <<  (string5 + "string6") << endl;
    
    string6 += "aaaaaaas";
    cout << string6 << endl;
    
}