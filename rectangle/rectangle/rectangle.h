#pragma once
#include <string>
#include <iostream>
#include <iomanip>


class rectangle {

private:
	std::string color;
	double length;
	double width;

public:
	rectangle() {
		setColor("Blue");
		setLength(0);
		setWidth(0);

	}

	rectangle(std::string c, double l, double w) {

		setLength(l);
		setWidth(w);

		if (c == "Red" || c == "Blue" || c == "White") {		//check if color is correctly spelled with proper caps, if not, change to white
			setColor(c);

		}
		else {
			setColor("White");

		}

	}

	void setColor(std::string c) {
		color = properCap(c);

	}

	void setLength(double l) {
		if (l < 0) {
			l = -l;				//alternatively, could use fabs() function

		}
		length = l;
	}

	void setWidth(double w) {
		if (w < 0) {
			w = -w;				//alternatively, could use fabs() function

		}
		width = w;

	}

	std::string getColor() {
		return color;

	}

	double getLength() {
		return length;

	}

	double getWidth() {
		return width;

	}

	static std::string properCap(std::string str) {

		str[0] = toupper(str[0]);

		for (int i = 1; i <= str.size(); i++) {

			str[i] = tolower(str[i]);

		}

		return str;

	}

	double getArea() {
		double l = getLength();
		double w = getWidth();

		double area = l * w;

		return area;

	}

	double getPerimeter() {
		double l = getLength();
		double w = getWidth();

		double perimeter = (2.0 * l) + (2.0 * w);

		return perimeter;

	}

	void toString() {

		std::cout << std::setprecision(2) << std::fixed << "Address:" << this << "\tType:" 
				  << "Rectangle\t" << "Length:" << getLength() << "\t" << "Width:" << getWidth() 
				  << "\t" << "Color:" << getColor() << "\t" << "Area:" << getArea() << "\t" 
				  << "Perimeter:" << getPerimeter() << "\n";

	}

	rectangle operator+ (rectangle r) {

		rectangle rect;
		rect.length = this->length + r.length;
		rect.width = this->width + r.width;
		rect.color = this->color + r.color;

		if (this->color == r.color) {

			rect.color = this->color;

		}
		else {

			rect.color = "White";

		}

		return rect;

	}

};