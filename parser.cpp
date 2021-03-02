#include <regex>
#include <iostream>
#include <string>
#include<iostream>
#include<regex>
#include<string>
#include<fstream>
#define regexIgnore "(\\s)*;(.)*"
#define regexG01 "G01|G1"
#define regexX "X(((\\+|-)?([0-9]+)(\\.[0-9]+)?)|((\\+|-)?\\.?[0-9]+))"
#define regexY "Y(((\\+|-)?([0-9]+)(\\.[0-9]+)?)|((\\+|-)?\\.?[0-9]+))"
#define regexZ "Z(((\\+|-)?([0-9]+)(\\.[0-9]+)?)|((\\+|-)?\\.?[0-9]+))"
#define regexF "F(((\\+|-)?([0-9]+)(\\.[0-9]+)?)|((\\+|-)?\\.?[0-9]+))"
const std::regex commentReg(regexIgnore);
const std::regex xReg(regexX);
const std::regex yReg(regexY);
const std::regex g01Reg(regexG01);
const std::regex zReg(regexZ);
const std::regex fReg(regexF);
std::string str("G1 X34.302 Y41.626 F1800.000");
int main()
{
	std::smatch match;
	std::cout << std::regex_search(str, match, yReg) << "\n";
	std::cout << match[1].str().erase(0, 0);
}