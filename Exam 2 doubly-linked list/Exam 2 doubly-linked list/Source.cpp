#include "node.h"
#include "DList.h"
using namespace std;

int main() {

	DList* lst1 = new DList();
	lst1->addFromDisk("T:\\myfile1.txt");
	lst1->showList();

	DList* lst2 = new DList();
	lst2->addFromDisk("T:\\myfile2.txt");
	lst2->showList();

	lst1->addWithoutDuplicates(lst2);
	lst1->showList();


}