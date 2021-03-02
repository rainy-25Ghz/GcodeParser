#include <regex>
#include <iostream>
#include <string>
const std::regex regx("X(((\\+|-)?([0-9]+)(\\.[0-9]+)?)|((\\+|-)?\\.?[0-9]+))");
std::string str("G1 X34.302 Y41.626 F1800.000");
int main()
{
	std::smatch match;
	std::cout << std::regex_search(str, match, regx) << "\n";
	std::cout << match[1].str().erase(0, 0);
}