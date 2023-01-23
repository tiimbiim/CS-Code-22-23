#pragma once
#include <string> 
#include <sstream> 
#include <vector> 
#include <iostream> 
#include <iomanip> 
using namespace std;

//Declaration section
class geometricObject {
private: 
	string color; 
	//utility routine to force text to proper cap format
	string properCap(string original); 

	//list of valid colors - children may reduce it but not enlarge it 
	vector<string> validColors{ "White",  "Red",  "Blue" }; 

public: 
	const double PI = 3.1415; 
	//Accessors-Mutators 
	void setColor(string c); 
	string getColor() { return color; }

	//Constructor
	geometricObject(string c =  "Blue") { setColor(c); }

	//User-defined functions 
	virtual string toString(); //Descendants MUST implement it
	virtual double calculateArea() = 0;//PURE VIRTUAL 
	virtual double calculatePerimeter() = 0; //PURE VIRTUAL
};  
//  IMPLEMENTATION SECTION --------------------------------------------------------- 
string geometricObject::toString() { 
	stringstream sout; 
	sout << this << " GeometricObject[Color: " << color <<  "]"  ; 
	return sout.str(); 
} 
// -------------------------------------------------------------------- 
string geometricObject::properCap(string original) { 
	string converted = ""; 
	char c = toupper(original[0]); 
	converted +=  c; 
	for   (int   i = 1; i < original.size(); i++) 
		converted +=  tolower(original[i]); 
	return converted; 
} 
// --------------------------------------------------------------------- 
void geometricObject::setColor(string colorValue){ 
	//force colorValue to be in proper cap format
	colorValue = properCap(colorValue);  
	//is the supplied colorValue a valid choice?
	bool found = false; 
	for (int i = 0; i < validColors.size(); i++) 
	{ 
		if  (validColors[i] ==  colorValue) 
		{ 
			found = true; 
			break; 
		} 
	} 
	if (!found) colorValue = "Blue";  //default color 
	//set the color to the supplied (or adjusted) color 
	color = colorValue; 
} 