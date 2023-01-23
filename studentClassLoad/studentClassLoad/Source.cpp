#include "student.h"
#include <fstream>
#include <map>


int main() {

	ifstream inFile;
	vector<student*> vDatabase;
	vector<string> vcourse;		//used to split the courses

	string id, name, courses, userInput, buf;

	map<string, int> mID;
	multimap<string, int> mmRoster;

	bool doneID = false;
	bool doneCourse = false;
	bool found = false;

	int index = 1;	
	
	inFile.open("T:\\student course load.txt", ifstream::out | ifstream::app);

	

	if (inFile.fail()) {

		cout << "The file failed to open.\n";

	}

	while (!inFile.eof()) {

		getline(inFile, id);
		getline(inFile, name);
		getline(inFile, courses, '#');

		stringstream ss(courses);
		
		while (ss >> buf) {															//splits the classes into single strings by newline characters
			vcourse.push_back(buf);

			for (int i = 0; i < vcourse.size(); i++) 
				mmRoster.insert(pair<string, int>(vcourse[i], index - 1));
			
		}


		student* sp = new student(id, name, vcourse);
		vDatabase.push_back(sp);

		mID[sp->getID()] = index - 1;

		vcourse.clear();
		index++;
		inFile.peek();
	}

	inFile.close();
	
	for (int i = 0; i < vDatabase.size(); i++) {

		cout << vDatabase.at(i)->toString();

	}

	cout << "\nMap mID\n";

	for (auto it = mID.cbegin(); it != mID.cend(); ++it) {

		cout << it->first << " " << it->second << "\n";

	}

	cout << "\nMap mmRoster\n";

	for (auto it = mmRoster.cbegin(); it != mmRoster.cend(); ++it) {

		cout << it->first << " " << it->second << "\n";

	}

	while (!doneID) {
		cout << "\nPlease enter an ID (0000-0000 to end): \n";
		cin >> userInput;

		auto itr = mID.find(userInput);

		if (itr != mID.end())
			cout << vDatabase.at(itr->second)->toString();

		else if (userInput == "0000-0000")
			doneID = true;
		
		else
			cout << "The ID you entered was not located.\n";

	}

	while (!doneCourse) {
		cout << "\nPlease enter a course name (NONE to end): \n";
		cin >> userInput;

		found = false;

		for (auto itr = mmRoster.begin(); itr != mmRoster.end(); itr++) {

			if (itr->first == userInput) {
				cout << vDatabase.at(itr->second)->toString();
				found = true;
			}

		}

		if (userInput == "NONE")
			doneCourse = true;

		else if (!found)
			cout << "The course you entered was not located.\n";
	}
}