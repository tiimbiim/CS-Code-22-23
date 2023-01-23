#include "Actor.h"

using namespace std;

Actor::Actor() {

	setFirstName(" ");
	setLastName(" ");
	setBirthYear(0000);

}

Actor::Actor(std::string fname, std::string lname, int yob) {

	setFirstName(fname);
	setLastName(lname);
	setBirthYear(yob);

}

	void Actor::setFirstName(std::string fname) {
		firstName = fname;
	}
	std::string Actor::getFirstName() {
		return firstName;
	}

	void Actor::setLastName(std::string lname) {
		lastName = lname;
	}
	std::string Actor::getLastName() {
		return lastName;
	}

	void Actor::setBirthYear(int year) {
		birthYear = year;
	}
	int Actor::getBirthYear() {
		return birthYear;
	}