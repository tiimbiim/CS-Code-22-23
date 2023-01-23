#include "player.h"
#include <vector>
#include <iomanip>
#include <string>

int main() {

	std::ifstream inFile("C:\\temp\\soccer.txt");
	std::vector<player*> playerDatabase;
	
	std::string pName;
	std::string tName;
	std::string goalCount;
	std::string assistCount;
	std::string playTime;


	if (inFile.fail()) {

		std::cout << "The file does not exist.\n";
		return 0;

	}

	//std::cout << "before the while loop";

	while (!inFile.eof()) {

		
		std::getline(inFile, pName);
		std::getline(inFile, tName);
		std::getline(inFile, goalCount);
		std::getline(inFile, assistCount);
		std::getline(inFile, playTime);

		playerDatabase.push_back(new player(pName, tName, goalCount, assistCount, playTime));


	}

	inFile.close();
	
	std::cout << "Unsorted database\n";

	for (int i = 0; i < playerDatabase.size(); i++) {

		std::cout << playerDatabase.at(i)->toString();
		
	}

	std::cout << "\nSorted database\n";

	player::sortPlayerDB(playerDatabase); //database is now sorted

	for (int t = 0; t < playerDatabase.size(); t++) {

		std::cout << playerDatabase.at(t)->toString();

	}

}
