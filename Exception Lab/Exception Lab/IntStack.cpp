#include <vector>
#include <iostream>
#include "exceptions.h"
using namespace std;

class IntStack
{
public:
	// MaxSize should be an unsigned int, but for the sake of example...
	IntStack(int MaxSize)
	{
		if (MaxSize < 0)
		{
			throw InvalidSize("Cannot create a negative stack size");
		}

		data.resize(MaxSize);
		cur_index = 0;
	}

	void push(int new_data)
	{
		if (cur_index == data.size())
		{
			throw StackFull("Push to full stack", new_data);
		}
		else
		{
			data.at(cur_index) = new_data;
			cur_index++;
		}
	}

	int pop()
	{
		if (cur_index == 0)
		{
			throw StackEmpty("Pop from empty stack");
		}
		else
		{
			// pop off the int and return it
			cur_index--;
			return data.at(cur_index);
		}
	}

private:
	vector<int> data;
	unsigned int cur_index;
};

int main()
{
	try {
		// Testing Constructor
		IntStack c_test(-10);

		c_test.push(3);
		c_test.push(4);
		c_test.pop();
		c_test.pop();
	}
	catch (InvalidSize& e) {

		cerr << "Caught error: " << e.what() << endl;

	}
	

	try {
		// Testing push
		IntStack push_test(5);

		for (unsigned int i = 0; i < 7; i++) {
			push_test.push(i);
		}
	}
	catch (StackFull& e) {
		cerr << "Caught error: " << e.what() << ", Value " << e.getValue() << endl;
	}


	try {
		// Testing pop
		IntStack pop_test(2);

		pop_test.push(1);
		pop_test.push(2);
		pop_test.pop();
		pop_test.pop();
		pop_test.pop();
	}
	catch (StackEmpty& e) {
		cerr << "Caught error: " << e.what() << endl;
	}
	cout << "Completed!" << endl;
}