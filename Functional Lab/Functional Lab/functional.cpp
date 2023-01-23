#include <string>
#include<iostream>
#include <unordered_map>
#include <sstream>
#include<algorithm>
#include <iterator>

using namespace std;

	void print_pairs(vector<pair<int, string>> v) {

	}

	vector <pair<int, string>> sort_by_freq(vector <pair<int, string>> v) {



	}



	vector<string> words(string text) {

		istringstream iss;
		vector<string> tv{};

		for (string t; iss >> t;) {

			transform(text.begin(), text.end(), t, isalnum);

			tv.push_back(t);

		}

		return tv;

	}

	unordered_map<string, int>count_occurrences(vector<string> w) {

		string current_word = "";
		int counter;
		unordered_map<string, int> cw{};

		for (int i = 0; i < w.size(); i++) {

			current_word = w[i];
			counter = 1;

			for (int t = 0; t < w.size(); t++) {

				if (current_word == w[t]) {
					counter++;
				}

			}

			pair<string, int> occurrences(current_word, counter);

			cw.insert(occurrences);

		}

		return cw;
	}

	void printCommonWords(const string& text) {

		vector<string> w = words(text);
		unordered_map <string, int> m = count_occurrences(w);

		for (auto& i : m) {

			cout << i.second << " " << i.first << endl;

		}

	}

int main() {


	printCommonWords("Tim bim");

}