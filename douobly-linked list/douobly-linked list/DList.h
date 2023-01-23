#pragma once
#include "node.h"
#include <iostream>
#include <iomanip>
using namespace std;

class DList {

public:
	node* first;
	node* last;
	int counter;

	DList() {

		first = nullptr;
		last = nullptr;
		counter = 0;

	};

	void deleteNode(node* n) {

		if (n == nullptr) return;
		if (counter == 0) return;

		if (counter == 1) {
			first = nullptr;
			last = nullptr;
			counter = 0;
			return;
		}

		counter--;

		if (n == first) {
			first->next;
			delete n;
			return;
		}

		node* leftNode = n->previous;
		node* rightNode = n->next;

		if (n == last) {

			leftNode->next = nullptr;
			last = leftNode;
			delete n;
			return;

		}

		leftNode->next = rightNode;
		rightNode->previous = leftNode;
		delete n;
		return;
	}

	node* findNode(string keyData) {
		node* p = first;
		while (p != nullptr) {

			if (p->data == keyData)
				return p;
			p = p->next;

		}

		return 0;
	}

	void addFirst(node* n1) {

		n1->next = first;
		first->previous = n1;
		first = n1;
		counter++;

	}

	void addAfter(node* n1, node* n2) {

		if (n1 == nullptr) {

			n2->next = nullptr;
			last = n2;

			if (first == nullptr) {
				n2->previous = nullptr;
				first = n2; 
				counter++;
				return;
			}

			n2->next = n1->next;
			n1->next = n2;
			n2->previous = n1;
		}
		else{

			n2->next = n1->next;
			n1->next = n2;
			n2->previous = n1;


			if (n2->next != nullptr)
				n2->next->previous = n2;

		}
		
		last = n2;

		counter++;
		return;
	}

	void showList() {

		cout << endl;
		node* p = this->first;
		cout << " First: " << first
			<< "\tLast: " << last
			<< "\tCounter: " << counter << endl;
		while (p != nullptr) {

			cout << p->showNode() << endl;
			p = p->next;

		}

	}

	void showListBackwards() {

		cout << endl;
		node* p = this->last;
		cout << " First: " << first
			<< "\tLast: " << last
			<< "\tCounter: " << counter << endl;
		while (p != nullptr) {

			cout << p->showNode() << endl;
			p = p->previous;

		}

	}

};
