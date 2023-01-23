#pragma once
#include "geometricObject.h"

class triangle : public geometricObject
{

protected:
	double s[3];
	void utilityBubbleSort(double a[], int n);

public: 
	void setSides(double s0Value, double s1Value, double s2Value);

	double* getSides() {
		utilityBubbleSort(s, 3);
		return s;
		
	}

	triangle(double s0Value = 0, double s1Value = 0, double s2Value = 0, string colorValue = "White");




	string toString();
	double calculateArea();
	double calculatePerimeter();

};

triangle::triangle(double s0Value, double s1Value, double s2Value, string colorValue) : geometricObject(colorValue) {
	setSides(s0Value, s1Value, s2Value);

}

void triangle::utilityBubbleSort(double a[], int n) {
	double temp;

	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (a[j] > a[j + 1]) {
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
	
			
				
}
void triangle::setSides(double s0Value, double s1Value, double s2Value) {
	s[0] = s0Value;
	s[1] = s1Value;
	s[2] = s2Value;

	if (s[0] + s[1] < s[2] || s[0] + s[2] < s[1] || s[1] + s[2] < s[0]) {
		s[0] = 0;
		s[1] = 0;
		s[2] = 0;

	}

}
string triangle::toString() {
	stringstream sout;
	sout << fixed << setprecision(2) << this << " Triangle\t[Sides: " <<  *getSides() << ", " << *(getSides()+1) << ", " << *(getSides()+2) << "\tColor: " << color << "\tArea: "
		 << calculateArea() << "\tPerimeter: " << calculatePerimeter() << "]";
	return sout.str();
}
double triangle::calculateArea() {

	double S, A;

	S = (s[0] + s[1] + s[2]) / 2.0;
	A = sqrt(S * (S - s[0]) * (S - s[1]) * (S - s[2]));
	return A;

}
double triangle::calculatePerimeter() {

	double P = s[0] + s[1] + s[2];
	return P;
}