#include "Movie.h"

using namespace std;

Movie::Movie() {

	setMovieTime(0);
	setMovieYearOut(9999);
	setMovieTime(000);
	setMovieTitle("N/A");
	setNumberOfActors(0);
	actorArrayIndex = 0;

	//actors = new Actor[1];

}

Movie::Movie(int movieLength, int year, int numOfActors, double price, std::string title) {

	setMovieTime(movieLength);
	setMovieYearOut(year);
	setNumberOfActors(numOfActors);
	setMoviePrice(price);
	setMovieTitle(title);

	actorArrayIndex = 0;

	//actors = new Actor[numOfActors];

}

Movie::Movie(const Movie& m) {

	movieTime = m.movieTime;
	movieYearOut = m.movieYearOut;
	numberOfActors = m.numberOfActors;
	moviePrice = m.moviePrice;
	movieTitle = m.movieTitle;

	actors = new Actor[numberOfActors];
		
	for (int i = 0; i < numberOfActors; i++) {

		actors[i] = m.actors[i];

	}


}

Movie::~Movie() {

	delete[] actors;
	actors = NULL;

}

	void Movie::setMovieTime(int time) {
		movieTime = time;
	}
	int Movie::getMovieTime() {
		return movieTime;
	}

	void Movie::setMovieYearOut(int year) {
		movieYearOut = year;
	}
	int Movie::getMovieYearOut() {
		return movieYearOut;
	}

	void Movie::setNumberOfActors(int numActors) {
		numberOfActors = numActors;

		actors = new Actor[numberOfActors];

	}
	int Movie::getNumberOfActors() {
		return numberOfActors;
	}
	
	void Movie::setMoviePrice(double price) {
		moviePrice = price;
	}
	double Movie::getMoviePrice() {
		return moviePrice;
	}

	void Movie::setMovieTitle(std::string title) {
		movieTitle = title;
	}
	std::string Movie::getMovieTitle() {
		return movieTitle;
	}

	void Movie::addActor(std::string fn, std::string ln, int yob) {
		
		Actor a(fn, ln, yob);

		actors[actorArrayIndex] = a;

		actorArrayIndex++;

	}

	void Movie::printMovieInfo() {

		cout << "Title: " << getMovieTitle() << ", Published in: " << getMovieYearOut() << endl;
		
		cout << "Duration of Movie: " << getMovieTime() << " minutes" << endl;

		cout << "Price: $" << getMoviePrice() << endl;

		cout << "Actors:" << endl;

		for (int j = 0; j < numberOfActors; j++) {
			cout << actors[j].getFirstName() << " " << actors[j].getLastName() << ", " << actors[j].getBirthYear() << endl;
		}

	}