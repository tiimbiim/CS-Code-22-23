#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

class player {

private:
	std::string nameP;
	std::string nameT;
	/*int goal;
	int assist;
	int minutesPlayed;*/
	std::string goal;
	std::string assist;
	std::string minutesPlayed;
	double pI;
	

public:

	player(std::string name, std::string teamName, std::string goals, std::string assists, std::string minutes) {

		setName(name);
		setTeamName(teamName);
		setGoals(goals);
		setAssists(assists);
		setMinutes(minutes);

	}

	player() {

		setName("N/A");
		setTeamName("N/A");
		setGoals("0");
		setAssists("0");
		setMinutes("0");

	}

	//setters
	void setName(std::string name) {
		nameP = name;
	}

	void setTeamName(std::string teamName) {
		nameT = teamName;
	}

	void setGoals(std::string goals) {
		goal = goals;
	}

	void setAssists(std::string assists) {
		assist = assists;
	}

	void setMinutes(std::string minutes) {
		minutesPlayed = minutes;
	}


	//getters
	std::string getName() {
		return nameP;
	}

	std::string getTeamName() {
		return nameT;
	}

	std::string getGoals() {
		return goal;
	}

	std::string getAssists() {
		return assist;
	}

	std::string getMinutes() {
		return minutesPlayed;
	}

	double getPI() {
		double goals = std::stod(goal);
		double assists = std::stod(assist);
		double pI;

		pI = goals + (assists / 2.0);

		return pI;
		
	}

	//toString
	std::string toString() {

		std::ostringstream ossout;

		ossout << "Player [ Name:" << getName() << "\t\tTeam: " << getTeamName() << "\tGoals: " << getGoals() 
			   << "\tAssists: " << getAssists() << " ] " << getPI() << "\n";

		return ossout.str();

	}

	static void sortPlayerDB(std::vector<player*>& vector) {

		for (int i = vector.size() - 1; i >= 0; i--) {

			for (int t = 0; t < i; t++) {

				if (vector[t]->getPI() < vector[t + 1]->getPI()) {

					player temp = *vector[t];
					*vector[t] = *vector[t + 1];
					*vector[t + 1] = temp;
				}

			}

		}

	}
	
};


