#pragma once
#include <string>
#include <sstream>
using namespace std;

struct node {

	//Node layout is [pointersLeft, pointerRight, data]
	node* next;
	node* previous;
	string data;

	node(string newData) {

		data = newData;
		next = nullptr;
		previous = nullptr;

	};

	string showNode() {

		stringstream ss;
		ss << " "
			<< this
			<< " Node[Next: " << next
			<< " Previous: " << previous
			<< " Data: " << data
			<< "]";
		return ss.str();

	}

};
