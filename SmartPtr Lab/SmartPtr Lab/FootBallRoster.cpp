#include <memory>
#include <iostream>
#include <string>
#include <optional>
using namespace std;

struct FootBallPlayer {
	string name;
	int num;

};

struct node {

	FootBallPlayer f;
	shared_ptr<node> next;

};

class FootBallRoster {

private:
	shared_ptr<node> head;
	weak_ptr<node> fav;

public:
	// Adds a FootBallPlayer to the roster.
	void addPlayer(FootBallPlayer player);

	// deletes the first FootBallPlayer that matches name
	bool deletePlayer(string name);

	// Uses a weak_ptr to return true if the 
	bool setFavorite(string name);

	// Returns an optional parameter if there is a favorite player
	std::optional<FootBallPlayer> getFavorite() const;

	// Prints the list of FootBallPlayers on the roster
	void printPlayers() const;
};

void FootBallRoster::addPlayer(FootBallPlayer player) {
	
	shared_ptr<node> p = make_shared<node>();
	
	p->f = player;
	p->next = head;
	head = p;

}


bool FootBallRoster::deletePlayer(string name) {

	if (head == nullptr)
		return false;
	
	if (head->f.name == name) {
		
		shared_ptr<node> p = head;
		head = head->next;

		p->f.name = "";
		p->f.num = NULL;
		p = nullptr;

		return true;

	}

	shared_ptr<node> p = head;

	while (p != nullptr) {

		if (p->f.name == name) {

		
			p->f.name = "";
			p->f.num = NULL;
			p = nullptr;

			return true;

		}

		p = p->next;

	}

	return false;

}

bool FootBallRoster::setFavorite(string name) {

	shared_ptr<node> p = head;

	while (p != nullptr) {

		if (p->f.name == name) {

			fav = p;
			return true;

		}

		p = p->next;

	}

	return false;

	

}

std::optional<FootBallPlayer> FootBallRoster::getFavorite() const {

	shared_ptr<node> p = fav.lock();

	if (p)
		return p->f;
	else
		return {};

}


void FootBallRoster::printPlayers() const {

	shared_ptr<node> p = head;

	while (p != nullptr) {

		cout << p->f.name << " #" << p->f.num << endl;

		p = p->next;

	}

}




// prints out the name of the favorite player or a message 
// stating there is no favorite player.
void favoritePlayer(const FootBallRoster& roster) {

	if (roster.getFavorite() && roster.getFavorite()->name != "") {

		cout << "Favorite player: " << roster.getFavorite()->name << endl;

	}
	else {

		cout << "There is no favorite player" << endl;

	}
}


int main() {

	FootBallPlayer fb1{ "Matthew Stafford", 9 };
	FootBallPlayer fb2{ "Aaron Donald", 99 };
	FootBallPlayer fb3{ "Jalen Ramsey", 5 };

	FootBallRoster roster;

	roster.addPlayer(fb1);
	roster.addPlayer(fb2);
	roster.addPlayer(fb3);

	roster.printPlayers();
	roster.setFavorite("Aaron Donald");

	favoritePlayer(roster);

	roster.deletePlayer("Aaron Donald");
	favoritePlayer(roster);
 }