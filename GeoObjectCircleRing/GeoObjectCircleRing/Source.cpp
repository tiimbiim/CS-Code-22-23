#include "geometricObject.h"
#include "circle.h"
#include "ring.h"
using namespace std;

int main() {
	cout << "Solution created by Timothy Vu \n\n";

	cout << "Testing r1(10, 8, \"Red\")\n";
	try {
		ring r1(10, 8, "Red"); // (outer radius, inner radius, color)
		cout << r1.toString();
	}
	catch (const exception& e) {
		cout << e.what();
	}
	//--------------------------------------------------------------------------
	cout << "Testing r2(10, 11, \"WHITE\")\n";
	try {
		ring r2(10, 11, "WHITE");
		cout << r2.toString();
	}
	catch (const exception& e) {
		cout << e.what();
	}
	//--------------------------------------------------------------------------
	cout << "Testing r3(10, -1, \"BLUE\")\n";
	try {
		ring r3(10, -1, "BLUE");
		cout << r3.toString();
	}
	catch (const exception& e) {
		cout << e.what();
	}
	//---------------------------------------------------------------------------
	cout << "Testing r4(2, 1, \"YELLOW\")\n";
	try {
		ring r4(2, 1, "YELLOW");
		cout << r4.toString();
	}
	catch (const exception& e) {
		cout << e.what();
	}
}