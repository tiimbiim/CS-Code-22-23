#include <regex>
#include <string>
#include <iostream>

using namespace std;

int main() {

	string bim;

	while (bim != "9010") {

		cin >> bim;

		const bool containsRegex = regex_search("10:45\sam", regex("^([1-9]|(1[0-2])):[0-5][0-9](\s)(am|pm)$"));

		cout << boolalpha << containsRegex << "\n" << endl;
	}

	cout << "Goodbye" << endl;

}