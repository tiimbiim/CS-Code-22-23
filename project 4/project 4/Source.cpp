#include<iostream>
#include<fstream>
using namespace std;

bool process();

int main() {

	

}

bool process() {

	string fileContents;
	string fileName;

	cout << "Please enter a file name: " << endl;
	cin >> fileName;

	ifstream in(fileName);

	if(in.fail()) {

		cout << "Something has gone wrong." << endl;
		return false;

	}

	while(!in.eof()) {

		in >> fileContents;
		
	}

	cout << fileContents << endl;
	return true;

}