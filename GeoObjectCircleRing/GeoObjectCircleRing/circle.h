#pragma once
#include "GeometricObject.h" 
using namespace std; 

class circle : public geometricObject{ 

private: 
	double radius;

public: 
	//accessors-mutators 
	double getRadius() { return radius; }
	void setRadius(double radius) { this->radius = abs(radius); }

	//constructors
	circle(double radiusValue = 0, string colorValue = "Red") : geometricObject(colorValue) 
	{ 
		setRadius(radiusValue);  
	} 
	//programmer-defined methods 
	string toString() override; 
	double calculateArea() override { 
		return PI * radius * radius;
	} 
	double calculatePerimeter() override { 
		return 2 * PI * radius; 
	} 
}; 
// IMPLEMENTATION ----------------------------------------------------- 
string circle::toString() { 
	stringstream sout; 
	sout << fixed <<  setprecision(2);
	sout << this<<  " Circle[ Radius: " <<  getRadius() <<   " " <<  " Color: " <<  getColor()<<  " Area:  "
		 <<  calculateArea() <<  " Perimeter: " << calculatePerimeter() <<  " ] " << endl;

	return sout.str(); 
} 