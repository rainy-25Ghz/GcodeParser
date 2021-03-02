#include <regex>
#include <iostream>
#include <string>
#include<iostream>
#include<regex>
#include<string>
#include<fstream>
using namespace std;
#define regexIgnore "(\\s)*;(.)*"
#define regexG01 "G01|G1"
const char* regexX = R"(X[-+]?[0-9]*\.?[0-9]+)";
const char* regexY = R"(Y[-+]?[0-9]*\.?[0-9]+)";
const char* regexZ = R"(Z[-+]?[0-9]*\.?[0-9]+)";
#define regexF "F(((\\+|-)?([0-9]+)(\\.[0-9]+)?)|((\\+|-)?\\.?[0-9]+))"
const regex commentReg(regexIgnore);
const regex xReg(regexX);
const regex yReg(regexY);
const regex g01Reg(regexG01);
const regex zReg(regexZ);
const regex fReg(regexF);
string str("G1 X34.302 Y41.626 F1800.000");
int main()
{
    fstream newfile;
    vector<const char*> results(100000,"");
    
    newfile.open("test.gcode", ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()) {   //checking whether the file is open
        string line;
        int count = 0;
        smatch temp;//存储string match结果
        while (getline(newfile, line)) { //read data from file object and put it into string.
            
            if (regex_search(line,temp, zReg))
            {
                cout << temp[0].str().erase(0,1) << '\t' << count++ << "\n"; //print the data of the string
            }
        }
        newfile.close(); //close the file object.
    }
	/*smatch match;
	cout << std::regex_search(str, match, yReg) << "\n";
	cout << match[1].str().erase(0, 0);*/
}