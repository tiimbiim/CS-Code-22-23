#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <stdexcept>
using namespace std;
const int MAXRESULTS = 20;
const int MAXDICTWORDS = 30000;
int loadR(istream& dictfile, string dict[]);
int storeLoop(istream& dictfile, string dict[], int i);
int anagramR(string word, const string dict[], int size, string results[]);
void permutationWord(string word, int i, int wordMaxIndex, int& currCount, const string dict[], int size, string results[], int& checkFileCounter);
void permutationLoop(string word, int a, int wordMaxIndex, int maxSize, int b, int& currCount, const string dict[], int size, string results[], int& checkFileCounter);
void swap(char& a, char& b);
int checkFile(string targetWord, const string dict[], string results[], int maxWordsFile, int targetCount, int& i);
bool checkDuplicate(string targetWord, string results[], int i, int numwords);
// void printR(const string results[], int size);
// void printLoop(const string results[], int size, int i);

int main() {
	string results[MAXRESULTS];
	string dict[MAXDICTWORDS];
	ifstream dictfile; // file containing the list of words
	int nwords; // number of words read from dictionary
	string fileName = "C:\\Users\\timbi\\Desktop\\tmbm\\school\\college\\CS30\\words.txt";
	string word;
	// 1. get file name
	//cout << "Enter file name: ";
	//getline(cin, fileName);
	// 2. open file
	dictfile.open(fileName);
	cerr << "File to be opened: " << fileName << endl;
	// 3. check if file is empty or cannot be opened
	if (dictfile.fail()) {
		cout << "Failed to open file." << endl;
		return 0;
	}
	else if (dictfile.peek() == EOF) {
		cout << "File is empty." << endl;
		return 0;
	}
	// 4. proceed to store words
	nwords = loadR(dictfile, dict);
	cout << "There are: " << nwords + 1 << " words in the text file." << endl;
	// 5. obtain word for anagram check
	cout << "Please enter a string for an anagram: ";
	cin >> word;

		int numMatches = anagramR(word, dict, nwords, results);


		// check:
		cout << "number of matches: " << numMatches;

		if (!numMatches)
			cout << "No matches found" << endl;
		else
			// printR(results, numMatches);
			return 0;
	
}

int loadR(istream& dictfile, string dict[]) {
	// call another function to store
	int counter = 0;
	counter = storeLoop(dictfile, dict, 0);
	return counter;
}

int storeLoop(istream& dictfile, string dict[], int i) {
	string tempWord;
	if (dictfile.eof() == true || i > MAXDICTWORDS) {
		return -1;
	}
	getline(dictfile, tempWord);
	dict[i] = tempWord;
	return 1 + storeLoop(dictfile, dict, i + 1);
}

int anagramR(string word, const string dict[], int size, string results[]) {
	/* algorithm:
	a) take the word inputted by user and find all permutations of it ( in permutationWord funct )
	b) check in the text file if any permutations of the word are in it ( in permutationWord funct )
	c1) increase anagram count for each found match ( in permutationWord funct )
	c2) save found permutations from text file into the results array ( in checkFile funct )
	c3) make sure there are no duplicates saved
	d) return the anagram count */
	int anagramCount = 0;
	int checkFileCounter = 0;
	try {
		permutationWord(word, 0, word.size() - 1, anagramCount, dict, size, results, checkFileCounter);
	}
	catch (...) {

		cerr << "Something is wrong " << endl;

	}
	for (int k = 0; k < anagramCount; k++) {
		cout << results[k] << " ";
	}
	return anagramCount;
}


void permutationWord(string word, int i, int wordMaxIndex, int& currCount, const string dict[], int size, string results[], int& checkFileCounter) {
	if (i == wordMaxIndex) {
		currCount += checkFile(word, dict, results, size, 0, checkFileCounter);
		return;
	}
	else {
		permutationLoop(word, i, wordMaxIndex, word.size(), i, currCount, dict, size, results, checkFileCounter);
	}
}

void permutationLoop(string word, int a, int wordMaxIndex, int maxSize, int b, int& currCount, const string dict[], int size, string results[], int& checkFileCounter) {
	if (a >= maxSize) {
		return;
	}
	else {
		/* algorithm for permutation;
		a) swap characters (traverse)
		b) permutation on following character
		*/
		swap(word[b], word[a]);
		permutationWord(word, b + 1, wordMaxIndex, currCount, dict, size, results, checkFileCounter);
	}
	permutationLoop(word, a + 1, wordMaxIndex, maxSize, b, currCount, dict, size, results, checkFileCounter);
}

void swap(char& a, char& b) {
	char sub;
	sub = a;
	a = b;
	b = sub;
}

int checkFile(string targetWord, const string dict[], string results[], int maxWordsFile, int targetCount, int& i) {
	// base case
	if (i > MAXRESULTS || targetCount > maxWordsFile) {
		return 0;
	}

	if (targetWord == dict[targetCount]) {
		if (checkDuplicate(targetWord, results, 0, maxWordsFile) == true) {
			return 0;
		}
		// FIXME: 
		results[i] = targetWord;
		// CHECK: cout << i << ": " << results[i] << endl;
		i++;
		return 1 + checkFile(targetWord, dict, results, maxWordsFile, targetCount + 1, i);
	}
	return checkFile(targetWord, dict, results, maxWordsFile, targetCount + 1, i);
}

bool checkDuplicate(string targetWord, string results[], int i, int numwords) {
	if (i > numwords) {
		return false;
	}
	if (results[i] == targetWord) {
		return true;
	}
	return checkDuplicate(targetWord, results, i + 1, numwords);
}

