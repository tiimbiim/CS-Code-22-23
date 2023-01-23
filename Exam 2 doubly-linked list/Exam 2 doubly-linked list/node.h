#pragma once
#include <string>
#include <sstream>
using namespace std;

class node {

private:
	node* next;
	node* previous;
	string data;

public:
	node(string newData) {
		data = newData;
		next = nullptr;
		previous = nullptr;
	};

	string getData() { return data; }
	void setData(string newData) { data = newData; }
	node* getNext() { return next; }
	node* getPrevious() { return previous; }
	void setNext(node* newNext) { next = newNext; }
	void setPrevious(node* newPrevious) { previous = newPrevious; }

	string showNode() {
		stringstream ss;
		ss << this
			<< " Node[Next: " << next
			<< " Previous: " << previous
			<< " Data: " << data
			<< "]";
		return ss.str();
	}

};