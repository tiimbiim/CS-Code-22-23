#include "Movie.h"

using namespace std;

void test();

int main()
{
	cout << "Start testing\n" << endl;
	test();
	cout << "\nFinished testing" << endl;
	return 0;
}

void test()
{

	Movie m1(158, 2008, 3, 14.99, "The Dark Knight");

	m1.addActor("Heath", "Ledger", 1979);
	m1.addActor("Christian", "Bale", 1974);
	m1.addActor("Aaron", "Eckhart", 1964);

	Movie m2 = m1;

	m1.printMovieInfo();

	cout << endl;

	m2.printMovieInfo();

	cout << endl;

	Movie m3;

	m3.printMovieInfo();

	m3.setNumberOfActors(1);

	m3.addActor("Tim", "Bim", 2002);

	m3.printMovieInfo();

}