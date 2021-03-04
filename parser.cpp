#include <regex>
#include <iostream>
#include <string>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#define regexIgnore "(\\s)*;(.)*"
#define regexG01 "G01|G1"
#define isXY 1
#define isGZ 2
#define ignore 3
#define noPrev 0
string regexX = R"abc(X([-+]?[0-9]*\.?[0-9]+))abc";
string regexY = R"abc(Y([-+]?[0-9]*\.?[0-9]+))abc";
string regexZ = R"abc(Z([-+]?[0-9]*\.?[0-9]+))abc";
string regexF = R"abc(F([-+]?[0-9]*\.?[0-9]+))abc";
const regex commentReg(regexIgnore);
const regex xReg(regexX);
const regex yReg(regexY);
const regex g01Reg(regexG01);
const regex zReg(regexZ);
const regex fReg(regexF);
string str("G1 X34.302 Y41.626 F1800.000");

inline bool hasX(const string &line, smatch &X)
{
    return regex_search(line, X, xReg);
}
inline bool hasY(const string &line, smatch &Y)
{
    return regex_search(line, Y, yReg);
}
inline bool hasZ(const string &line, smatch &Z)
{
    return regex_search(line, Z, zReg);
}
void parse(fstream &file, vector<string> &acs_code)
{
    int count = 0;  //ACS指令的行数
    smatch X, Y, Z; //存储string match结果
    string curr = "", prev = "";
    int prev_flag = noPrev;
    while (getline(file, curr))
    { //read data from file object and put it into string.
        if (regex_search(curr, g01Reg))
        {
            if (hasX(curr, X) && hasY(curr, Y))
            {
                if (prev_flag == isXY)
                {
                    acs_code[count] = "LINE (0,1),  " + to_string(stod(X.str(1)) - 50.0) + ",  " + to_string(stod(Y.str(1)) - 50.0) + "\n";
                    cout << acs_code[count];
                }
                else
                {
                    /*PTP/e (0,1) ,-14.791000, -9.055000
                        XSEG/h (0,1) ,-14.791000, -9.055000,  10*/
                    acs_code[count] = "PTP/e (0,1),  " + to_string(stod(X.str(1)) - 50.0) + ",  " + to_string(stof(Y.str(1)) - 50) + "\n";
                    count++;
                    acs_code[count] = "XSEG/h (0,1),  " + to_string(stod(X.str(1)) - 50.0) + ",  " + to_string(stod(Y.str(1)) - 50) + ",  " + "10" + "\n";
                    cout << acs_code[count];
                }
                count++;
                prev_flag = isXY;
                continue;
            }
            if (count > 0 && (acs_code[count - 1][0] == 'L' || acs_code[count - 1][0] == 'X'))
            {
                acs_code[count] = "ENDS (0,1)\n";
                cout << acs_code[count];
                count++;
                prev_flag = ignore;
            }
            if (hasZ(curr, Z))
            {
                acs_code[count] = "PTP/e 2,  " + Z.str(1) + "\n";
                cout << acs_code[count];
                count++;
                prev_flag = isGZ;
                continue;
            }
        }
        prev = curr;
        prev_flag = ignore;
    }
}
int main()
{
    fstream newfile, compiled;
    vector<string> results(100000, "");

    newfile.open("test.gcode", ios::in); //open a file to perform read operation using file object
    compiled.open("compiled.prg", ios::out);
    if (newfile.is_open() && compiled.is_open())
    { //checking whether the file is open
        parse(newfile, results);
        newfile.close(); //close the file object.
        for (auto line : results)
        {
            compiled << line;
        }
        compiled << "STOP";
    }
    /*smatch match;
	cout << std::regex_search(str, match, yReg) << "\n";
	cout << match[1].str().erase(0, 0);*/
}