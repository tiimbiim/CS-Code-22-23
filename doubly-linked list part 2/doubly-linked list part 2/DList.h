#pragma once
#include "node.h"
#include <iostream>
#include <iomanip>
#include <fstream>
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

	void mergeInOrder(DList* lst2) {

		node* nL = this->last;
		node* nF = this->first;
		node* n2 = lst2->first;

		bool done = false;

		while (!done) {

			while (nL->getData() > n2->getData() || nL == nullptr) {

				node* temp = new node(n2->getData());

				if (nL == nF) {

					this->addAfter(first, temp);
					break;
				}
				else {

					nL = nL->getPrevious();
				}

				if (nL->getData() < temp->getData())
					this->addAfter(nL, temp);
			}

			n2 = n2->getNext();
			nL = this->last;

			if (n2 == nullptr) {
				done = true;
			}
		}
	}

	void addFromDisk(string fileName) {
		string data1;
		ifstream inFile(fileName);

		while (!inFile.eof()) {
			getline(inFile, data1);
			node* n1 = new node(data1);

			if (counter == 0) {
				first = n1;
				last = n1;
				counter = 1;
			}
			else {

				n1->setPrevious(last);
				n1->setNext(last->getNext());
				last->setNext(n1);
				last = n1;
				counter++;
			}

			inFile.peek();
		}
	}

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

			first = first->getNext();
			first->setPrevious(nullptr);
			delete n;
			return;

		}

		node* leftNode = n->getPrevious();
		node* rightNode = n->getNext();

		if (n == last) {

			leftNode->setNext(nullptr);
			last = leftNode;
			delete n;
			return;

		}

		leftNode->setNext(rightNode);
		rightNode->setPrevious(leftNode);
		delete n;
		return;

	}

	node* findNode(string keyData) {

		node* p = first;
		while (p != nullptr) {

			string spy = p->data;
			if (p->data == keyData)
				return p;
			else
				p = p->getNext();

		}

		return p;

	}

	void addFirst(node* n1) {

		if (first == nullptr) {

			first = n1;
			last = n1;
			counter = 1;
			return;

		}

		n1->setNext(first);
		first->setPrevious(n1);
		first = n1;
		counter++;

	}

	void addAfter(node* n1, node* n2) {

		if (n1 == first) {

			n2->setNext(first);
			first->setPrevious(n2);
			first = n2;
			counter++;
			return;

		}

		if (counter == 0) {

			first = n2;
			last = n2;
			counter = 1;
			return;

		}

		counter++;

		node* n1Successor = n1->getNext();
		
		if (n1Successor != nullptr)
			n1Successor->setPrevious(n2);

		n1->setNext(n2);

		n2->setNext(n1Successor);
		n2->setPrevious(n1);

		if (n2->getNext() == nullptr) {

			last = n2;

		}

	}

	void showList() {

		int n = 1;
		cout << endl
			<< " First:" << first
			<< " Last:" << last
			<< " Counter:" << counter << endl;

		node* p = this->first;
		
		while (p != nullptr) {

			cout << setw(3) << n++ << "  "
				<< p->showNode() << endl;

			p = p->getNext();

		}

	}

	void showListBackwards() {

		cout << endl;
		node* p = this->last;

		while (p != nullptr) {

			cout << p->showNode() << endl;
			
			p = p->getPrevious();

		}

	}

};