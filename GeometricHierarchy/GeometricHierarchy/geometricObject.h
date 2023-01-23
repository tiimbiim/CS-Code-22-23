#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

class geometricObject {

protected:
	string color;
	string properCap(string original);
	vector<string> validColors{ "White", "Red", "Blue" };

public:
	const double PI = 3.1415;
	void setColor(string c);

	string getColor() {
		return color;

	}

	geometricObject(string c = "Blue") {
		setColor(c);

	}

	virtual string toString();

	virtual double calculateArea() = 0;
	virtual double calculatePerimeter() = 0;
};

string geometricObject::toString() {
	stringstream sout;
	sout << this << "geometricObject[Color: " << color << "]";
	return sout.str();

}
string geometricObject::properCap(string original) {
	string converted = "";
	char c = toupper(original[0]);
	converted += c;
	
	for (int i = 1; i < original.size(); i++) {
		converted += tolower(original[i]);

	}

	return converted;
}
void geometricObject::setColor(string colorValue) {
	colorValue = properCap(colorValue);
	bool found = false;
	for (int i = 0; i < validColors.size(); i++) {

		if (validColors[i] == colorValue) {
			found = true;
			break;

		}

	}
	if (!found) colorValue = "Blue";

	color = colorValue;
}
