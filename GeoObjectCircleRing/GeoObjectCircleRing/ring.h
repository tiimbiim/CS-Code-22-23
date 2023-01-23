#pragma once
#include "circle.h"

class ring : public circle {

private:
	double innerRadius;

public:
	double getInnerRadius() { return innerRadius; }
	double setInnerRadius(double innerRadius) { return this->innerRadius = innerRadius; }

	ring(double radiusValue = 0, double innerRadiusValue = 0, string colorValue = "Red") 
		: circle(radiusValue, colorValue)
	{
		if (innerRadiusValue > radiusValue || innerRadiusValue < 0) {
			throw exception("Invalid ring -- inner radius violation!\n\n");
		}
		setInnerRadius(innerRadiusValue);

	}
	
	double calculateArea() override {
		return (PI * getRadius() * getRadius()) - (PI * getInnerRadius() * getInnerRadius());
	}
	double calculatePerimeter() override {
		return PI * getInnerRadius() * 2.0;
	}

	string toString() override;
};
string ring::toString() {
	stringstream sout;
	sout << fixed << setprecision(3);
	sout << this << " Ring[ Inner Radius: " << getInnerRadius() << ", " << " Outer Radius: " << getRadius() << ", " << " Color: " << getColor() << ", Area: "
		<< calculateArea() << ", Inner Perimeter: " << calculatePerimeter() << " ] " << "\n\n";

	return sout.str();

}