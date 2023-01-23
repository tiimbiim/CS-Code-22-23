	#pragma once   
#include "node.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stack>
#include <set>
using namespace std;   

class DList {
public:
	node* first;
	node* last;
	int   counter;

	DList() {
		first = nullptr;
		last = nullptr;
		counter = 0;
	};
	
	~DList() {
		this->clear();
		cout << "DList at " << this << " has been destroyed\n";
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
	int addWithoutDuplicates(DList* lst2) {
		this->keepCommonElement(lst2);

		node* nL = this->last;
		node* nF = this->first;
		node* n2 = lst2->first;
		set<string> keyData;
	
		while (n2 != nullptr) {

			if (keyData.count(n2->getData()) == 0) {
				keyData.insert(n2->getData());
				node* temp = new node(n2->getData());
				nL->setNext(temp);
				temp->setPrevious(nL);
				nL = temp;
				counter++;
			}
			n2 = n2->getNext();
		}

		return 1;
	}
	
	void reverse() {
		stack <string> stk;
		node* ptr = first;

		while (ptr == first) {
			stk.push(ptr->getData());
			ptr = ptr->getNext();
		}

		ptr = first;

		while (ptr != nullptr) {
			ptr->setData(stk.top());
			stk.pop();
			ptr = ptr->getNext();
		}
	}

	void keepCommonElement(DList* lst2) {
		node* n1 = this->first;
		node* tempNext;

		while (n1 != nullptr) {
			string keyData = n1->getData();

			if (lst2->findNode(keyData) != nullptr) {
				tempNext = n1->getNext();
				this->deleteNode(n1);
				n1 = tempNext;
			}
			else {
				n1 = n1->getNext();
			}
		}
	}

	void deleteNode(node* n) {
		if (n == nullptr) return;
		if (counter == 0) return;

		if (counter == 1) {
			
			if (first != n) return;
			delete n;
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

			if (p->getData() == keyData)
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
		if (n1 == nullptr && counter > 0) {
			n2->setNext(first);
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

		n2->setNext(n2);
		n2->setNext(n1Successor);
		n2->setPrevious(n1);

		if (n2->getNext() == nullptr)
			last = n2;
	}

	void showList(string msg = "") {
		int n = 1;
		cout << endl
			<< msg
			<< " Loc:" << this
			<< " First:" << first
			<< " Last:" << last
			<< " Counter:" << counter << endl;
		node* p = this->first;

		while (p != nullptr) {
			cout << setw(3) << n++ << " " << p->showNode() << endl;
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

	void clear() {
		node* ptr = this->first;

		while (ptr != nullptr) {
			node* nextNode = ptr->getNext(); 
			this->deleteNode(ptr);
			ptr = nextNode;
		}
	}
};