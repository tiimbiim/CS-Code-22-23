#include <triangle.h>

using namespace std;

int main() {
	
	cout << "Solution created by Timothy Vu Spring 2021.\n";

	triangle t0;
	cout << "t0 " << t0.toString() << "\n";

	triangle t1(3, 5, 4, "BLUE");
	cout << "t1 " << t1.toString() << "\n";

	triangle t2(4, 6, 3, "red");
	cout << "t2 " << t2.toString() << "\n";

	triangle t3(9, 6, 4, "white");
	cout << "t3 " << t3.toString() << "\n";

}