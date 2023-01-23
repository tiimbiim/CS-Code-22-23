#include <rectangle.h>

int main() {

	rectangle r1, r3;
	rectangle r2("blue", 10, 20);

	r1.setLength(1);
	r1.setWidth(-2);
	r1.setColor("RED");

	r1.toString();
	r2.toString();

	r3 = r1 + r2;

	r3.toString();
}

