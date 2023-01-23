#include <iostream>
#include <cmath>
#include <string>
using namespace std;
int main()
{

	double deposit;
	double rate;
	int numComp;
	double years;

	double totalAccumulation;
	int dollars;
	int cents;

	double totalPennies;
	int roundedPennies;
	

	cout << "Hello, welcome to the compound interest program.\n";
	cout << "Please enter the amount to be deposited: ";
	cin >> deposit;
	
	cout << "Please enter the annual interest rate in decimalized fraction form (ie 9.8% becomes .098): ";
	cin >> rate;

	cout << "Please enter the number of compounding per year: ";
	cin >> numComp;

	cout << "Please enter the number of years the deposit will be left: ";
	cin >> years;

	totalAccumulation = deposit * pow((1 + rate/numComp), years*numComp);
	cout << "Raw accumulation is: " << totalAccumulation << "\n";

	totalPennies = totalAccumulation * 100;
	roundedPennies = int(totalPennies + 0.5);
	dollars = roundedPennies / 100;
	cents = roundedPennies % 100;

	cout << "Your accumulation is " << dollars << " dollars and " << cents << " cents.";



}