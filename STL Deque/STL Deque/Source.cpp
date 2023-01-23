#include <iostream>
#include <deque>
using namespace std;

deque<int> removeItemsReverseOrder(deque<int> d1, deque<int> d2);

int main() {

	deque<int> d1{ 20, 10, 15, 30, 7 };
	deque<int> d2{ 7, 15 };

	cout << "d1: ";
	for (int i : d1) {

		cout << i << " ";

	}

	cout << "\nd2: ";
	for (int j : d2) {

		cout << j << " ";

	}

	removeItemsReverseOrder(d1, d2);

}

deque<int> removeItemsReverseOrder(deque<int> d1, deque<int> d2) {

	deque<int> d3;
	deque<int> d1Temp;
	deque<int> d2Temp;

	int temp;

	d1Temp = d1;
	d2Temp = d2;

		while (!d2Temp.empty()) {

			if (d1Temp.front() != d2Temp.front()) {

				temp = d1Temp.front();
				d1Temp.push_back(temp);
				d1Temp.pop_front();

			}

			if (d1Temp.front() == d2Temp.front()) {

				d1Temp.pop_front();
				d2Temp.pop_front();

			}

		}

		d3 = d1Temp;

		cout << "\nd3: ";
		for (int t : d3) {

			cout << t << " ";

		}
		cout << "\n\n";

	return d3;
}