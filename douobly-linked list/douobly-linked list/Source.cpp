#include <iostream>
#include <string>
#include "node.h"
#include "DList.h"
using namespace std;

int main() {
	
	node* n1 = new node("AAA");
	node* n2 = new node("BBB");
	node* n3 = new node("CCC");
	
	DList* lst1 = new DList();
	
	lst1->addAfter(lst1->last, n1);
	lst1->addAfter(lst1->last, n2);
	lst1->addAfter(lst1->last, n3);
	

	cout << "\n List (Forward Traversal)";
	lst1->showList();
	
	cout << "\n List (Backward traversal)";
	lst1->showListBackwards();
	
	node* n4 = new node("AAB");
	lst1->addAfter(lst1->first, n4);
	
	cout << "\n List (Forward Traversal)";
	lst1->showList();
	
	cout << "\n List (Forward Traversal) - XXX is first node";
	lst1->addFirst(new node("XXX"));
	lst1->showList();
	
	string keyData = "BBB";
	node* p = lst1->findNode(keyData);
	cout << "\n Find node: " << keyData << " " << p;
	if (p != nullptr) {
		cout << "\n FOUND " << p->showNode() << endl;
	}

	cout << "\n List (Forward Traversal) - add YYY after BBB";
	lst1->addAfter(p, new node("YYY"));
	lst1->showList();

	cout << "\n List (Forward Traversal) - find and delete BBB";
	p = lst1->findNode("BBB");
	lst1->deleteNode(p);
	lst1->showList();
	
	cout << "\n All done... \n";

}
