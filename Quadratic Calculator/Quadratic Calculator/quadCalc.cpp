#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std; 
int main()
{
	int a;
	int b;
	int c;

	double x;
	double discriminant;
	double rootValue;

	cout << scientific;

	cout << "Hello, welcome to the quadratic formula solver. This program only works if a, b, and c are integers, and a is not zero.\n";
	cout << "Please enter a value for a: ";
	cin >> a;
	if (a == 0) {
		cout << "You have inputted a as 0. This will create a linear equation. Please continue if you wish to solve bx+c=0.\n";
	}

	cout << "Please enter a value for b: ";
	cin >> b;
	if (a == 0 && b == 0) {
		cout << "Because a and b are 0, this is no longer an algebraic equation. There is nothing to solve for.\n";
		return 0;
	}

	cout << "Please enter a value for c: ";
	cin >> c;
	if (a == 0 && b != 0 && c != 0) {
		x = double(-c) / double(b);
		cout << "The solution is: " << x;
		return 0;
	}

	discriminant = (b * b) - (4 * a * c);

	if (discriminant > 0) {
		x = (-b + sqrt((b * b) - 4 * a * c)) / (2 * a);
		cout << setprecision(4) << "There are two real solutions: " << x;
		x = (-b - sqrt((b * b) - 4 * a * c)) / (2 * a);
		cout << setprecision(4) << " and " << x;
	}
	else if (discriminant < 0) {
		if (b == 0) {
			rootValue = sqrt(abs((b * b) - (4 * a * c))) / (2 * a);
			cout << "There are two imaginary solutions: " << rootValue << "*I";
			rootValue = -sqrt(abs((b * b) - (4 * a * c))) / (2 * a);
			cout << setprecision(5) << " and " << rootValue << "*I";
		}
		else {
			x = double(-b) / (2 * double(a));
			rootValue = +sqrt(abs((b * b) - (4 * a * c))) / (2 * a);
			cout << setprecision(4) << "There are two imaginary solutions: " << x << rootValue << "*I";
			x = double(-b) / (2 * double(a));
			rootValue = -sqrt(abs((b * b) - (4 * a * c))) / (2 * a);
			cout << setprecision(4) << " and " << x << rootValue << "*I";
		}
	}
	else {
		x = (-b + sqrt((b * b) - 4 * a * c)) / (2 * a);
		cout << setprecision(4) << "There is only one real solution: " << x;
	}
}