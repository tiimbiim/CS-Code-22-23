#pragma once
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class student {

private:
	string id;
	string name;
	vector<string> vcourse;

public:

	student(string id, string name, vector<string> vCourse) {
		setID(id);
		setName(name);
		setCourse(vCourse);

	}

	void setName(string name) {
		this->name = name;

	}

	void setID(string id) {
		this->id = id;

	}

	void setCourse(vector<string> vCourse) {
		vcourse = vCourse;
	}

	string getName() {
		return this->name;

	}

	string getID() {
		return this->id;

	}

	string getCourses() {
		stringstream csout;

		for (int i = 0; i < vcourse.size(); i++) {
			csout << vcourse.at(i) << ", ";
			
		}

		return csout.str();

	}

	string toString() {
		stringstream ssout;
		ssout << this << " Student [ID: " << getID() << ", Name: " << getName() << ", Courses: { " << getCourses() << "}]\n" ;

		return ssout.str();

	}
};