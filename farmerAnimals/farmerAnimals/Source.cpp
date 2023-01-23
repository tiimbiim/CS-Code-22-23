/*
author: Timothy Vu
This program will compute all combinations a farmer could make buying 100 animals with 100 dollars
*/

#include <iostream>
using namespace std;
int main() {

	double cowPrice = 10.00;
	double pigPrice = 3.00;
	double chickenPrice = 0.50;

		for (int chick = 1; chick <= 98; chick++) {

			for (int pig = 1; pig <= 98; pig++) {

				for (int cow = 1; cow <= 98; cow++) {

					if (cow + pig + chick == 100 && (cow * cowPrice) + (pig * pigPrice) + (chick * chickenPrice) == 100) {

						cout << "The solution is " << cow << " cows, " << pig << " pigs, and " << chick << " chickens.";

					}

				}

			}

		}

}
