#include <iostream>
#include <fstream>
#include <istream>
#include <string>
using namespace std;

const int MAXRESULTS = 20;
const int MAXDICTWORDS = 30000;

int loadR(istream& dictfile, string dict[]);
int storeLoop(istream& dictfile, string dict[], int i);
int anagramR(string word, const string dict[], int size, string results[]);
void permutationWord(string word, const string dict[], string results[], int i, int wordLength, int& anagramCount, int numWords, int& checkFileCount);
void permutationLoop(string word, int a, int b, int wordLength, int wordMaxSize, int& anagramCount, const string dict[], int numWords, string results[], int& checkFileCount);
void swap(char& a, char& b);
int checkFile(string targetWord, const string dict[], string results[], int numWords, int targetCount, int& init);
bool checkDuplicate(string targetWord, string results[], int i, int numwords);
void printR(const string results[], int size);
void printLoop(const string results[], int numMatches, int i);


int main() {
	//string results[MAXRESULTS];
	//string dict[MAXDICTWORDS];
	//ifstream dictfile;  // file containing the list of words
	//int nwords;		   // number of words read from dictionary
	//string fileName = "C:\\Users\\timbi\\Desktop\\tmbm\\school\\college\\CS30\\words.txt";
	//string word;

	//// 1. get file name
	////cout << "Enter file name: ";
	////getline(cin, fileName);
	//// 2. open file
	//dictfile.open(fileName);
	//cout << "Opening " << fileName << endl;
	//// 3. check if file is empty or cannot be opened
	//if (dictfile.fail()) {
	//	cout << "Failed to open file." << endl;
	//	return 0;
	//}
	//else if (dictfile.peek() == EOF) {
	//	cout << "File is empty." << endl;
	//	return 0;
	//}
	//// 4. proceed to store words
	//nwords = loadR(dictfile, dict);
	//cout << "There are: " << nwords << " words in the text file." << endl;


	//// 5. obtain word for anagram check
	//cout << "Please enter a string for an anagram: ";
	//cin >> word;

	//// 6. obtain number of matches in file for anagram
	//int numMatches = anagramR(word, dict, nwords, results);
	//// cout << "found matches: " << numMatches << endl;

	//if (!numMatches)
	//	cout << "No matches found" << endl;
	//else
	//	printR(results, numMatches);

	//dictfile.close();
	//return 0; 

	shared_ptr<int> sp(make_shared<int>(2));
	weak_ptr<int> wp = sp;
	*wp = 3;

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
	int anagramCount = 0;
	int checkFileCount = 0;

	permutationWord(word, dict, results, 0, word.size() - 1, anagramCount, size, checkFileCount);

	/*for (int k = 0; k < anagramCount; k++) {
		cout << results[k] << ".." << endl;
	} */

	return anagramCount;
}

void permutationWord(string word, const string dict[], string results[], int i, int wordLength, int& anagramCount, int numWords, int& checkFileCount) {
	// wordLength value is length of word - 1
	if (i == wordLength) {
		anagramCount += checkFile(word, dict, results, numWords, 0, checkFileCount);
		// cout << word <<  endl;
		return;
	}
	else {
		permutationLoop(word, i, i, wordLength, word.size(), anagramCount, dict, numWords, results, checkFileCount);
	}
}

void permutationLoop(string word, int a, int b, int wordLength, int wordMaxSize, int& anagramCount, const string dict[], int numWords, string results[], int& checkFileCount) {
	if (a == wordMaxSize) {
		return;
	}
	else {
		swap(word[b], word[a]);
		permutationWord(word, dict, results, b + 1, wordLength, anagramCount, numWords, checkFileCount);
	}
	permutationLoop(word, a + 1, b, wordLength, wordMaxSize, anagramCount, dict, numWords, results, checkFileCount);
}

void swap(char& a, char& b) {
	char sub;
	sub = a;
	a = b;
	b = sub;
}

int checkFile(string targetWord, const string dict[], string results[], int numWords, int targetCount, int& init) {
	// base case
	if (init > MAXRESULTS || targetCount > numWords) {
		return 0;
	}

	if (targetWord == dict[targetCount]) {
		if (checkDuplicate(targetWord, results, 0, numWords) == true) {
			return 0;
		}
		// FIXME: 
		results[init] = targetWord;
		// cout << results[init] << endl;
		init++;
		return 1 + checkFile(targetWord, dict, results, numWords, targetCount + 1, init);
	}
	return checkFile(targetWord, dict, results, numWords, targetCount + 1, init);
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

void printR(const string results[], int size) {
	int i = 0;
	cout << "found matches in file: " << size << endl << endl;
	cout << "results list: " << endl;
	printLoop(results, size, i);

	cout << "thank you!" << endl;
}

void printLoop(const string results[], int numMatches, int i) {
	if (i >= numMatches) {
		return;
	}
	else {
		cout << results[i] << endl;
	}
	printLoop(results, numMatches, i + 1);
}