#include <iostream>
#include <cstdlib>
#include<ctime>
using namespace std;

const int MAXGUESS = 100;  // range is [0,MAXGUESS]
int maxBS = MAXGUESS, minBS = 0;

void DisplayMenu();

// Polymorphic classes

class Player {
public:
    // int min, max;
    virtual int getGuess() {
        return 0;
    }
    virtual void storeMinValue(int min) {}
    virtual void storeMaxValue(int max) {}
};

class HumanPlayer : public Player {
public:
    virtual int getGuess() {
        int human_guess;
        cout << "Enter your guess number between 0 and " << MAXGUESS << ": ";
        cin >> human_guess;

        return human_guess;
    }

    virtual void storeMinValue(int min_guess) {
        if (minBS >= min_guess) {
            return;
        }
        minBS = min_guess + 1;
    }
    virtual void storeMaxValue(int max_guess) {
        if (maxBS <= max_guess) {
            return;
        }
        maxBS = max_guess - 1;
    }
};


// ComputerPlayer does not use binary search.. just use random number generator
class ComputerPlayer : public Player {
public:
    int getGuess() {

        // if range is closed in on one value
        if (minBS == maxBS) {
            return minBS;
        }

        srand(time(NULL)); // intialize random num gen.
        int r = rand() % MAXGUESS + 1; // 1 to MAXGUESS, MAXGUESS + 1
                                    

        cout << "THIS IS RAND() IN CP: " << r << endl;

        return r;
    }

    virtual void storeMinValue(int min_guess) {
        if (minBS >= min_guess) {
            return;
        }
        minBS = min_guess + 1;
    }
    virtual void storeMaxValue(int max_guess) {
        if (maxBS <= max_guess) {
            return;
        }
        maxBS = max_guess - 1;
    }
};

class SmartComputerPlayer : public ComputerPlayer {
public:
    virtual int getGuess() {
        // if range is closed in on one value
        if (minBS == maxBS) {
            return minBS;
        }

        srand(time(NULL));
        int r = minBS + (rand() % (maxBS - minBS));

        

        return r;
    }
    virtual void storeMinValue(int min_guess) {
        if (minBS >= min_guess) {
            return;
        }
        minBS = min_guess + 1;
    }
    virtual void storeMaxValue(int max_guess) {
        if (maxBS <= max_guess) {
            return;
        }
        maxBS = max_guess - 1;
    }
};

// You can change this however you want
bool checkForWin(int guess, int answer) {

    if (answer > guess) {
        cout << "Your guess is too low" << endl;
    }
    else if (answer < guess) {
        cout << "Your guess is too high." << endl;
    }
    else {
        cout << "Your guess is correct!" << endl;
        return true;
    }
    return  false;
}


int play(Player& player1, Player& player2) {  // do not change this line
    // change anything you like below this line
    int answer = 0, guess = 0;
    int numGuesses = 0;

    srand(time(NULL));
    answer = rand() % MAXGUESS + 1;

    cout << "Answer: " << answer << endl;

    bool win = false;


    while (!win) {
        cout << "Player 1's turn to guess." << endl;
        guess = player1.getGuess();
        cout << "Player 1 Guess: " << guess << endl;
        numGuesses++;
        win = checkForWin(guess, answer);
        if (win) break;

        // storing values for binary search:
        if (guess < answer) { // too low
            player1.storeMinValue(guess);
        }
        else if (guess > answer) { // too high
            player1.storeMaxValue(guess);
        }
        cout << "Range: " << minBS << " - " << maxBS << endl;


        cout << "\nPlayer 2's turn to guess." << endl;
        guess = player2.getGuess();
        cout << "Player 2 Guess: " << guess << endl;
        numGuesses++;
        win = checkForWin(guess, answer);
        if (win) break;

        // storing values for binary search:
        if (guess < answer) { // too low
            player2.storeMinValue(guess);
        }
        else if (guess > answer) { // too high
            player2.storeMaxValue(guess);
        }
        cout << "Range: " << minBS << " - " << maxBS << endl;

        cout << "-----------------------" << endl << endl;
    }

    return numGuesses;
}

int main() {
    int userMenuChoice = 0;
    HumanPlayer hp1, hp2;
    ComputerPlayer cp1, cp2;
    SmartComputerPlayer scp1, scp2;

    DisplayMenu();
    cout << "Enter Option Number: ";
    cin >> userMenuChoice;

    switch (userMenuChoice) {
    case 1: // 1: human v. 2: human
        play(hp1, hp2);
        break;
    case 2: // 1: human v. 2: computer
        play(hp1, cp1);
        break;
    case 3: // 1: computer v. 2: computer
        play(cp1, cp2);
        break;
    case 4: // 1: computer v. 2: human
        play(cp1, hp1);
        break;
    case 5: // 1: human v. 2: smart 
        play(hp1, scp1);
        break;
    case 6: // 1: computer v. 2: smart
        play(cp1, scp1);
        break;
    case 7:
        play(scp1, scp2);
        break;
    case 8:
        play(scp1, cp1);
    case 9:
        exit(0); // hard stop
        break;
    default:
        cout << "Error. Invalid input." << endl;
        break;
    }

    return 0;
}

void DisplayMenu() {
    cout << "Option 1) Player 1: Human and Player 2: Human" << endl;
    cout << "Option 2) Player 1: Human and Player 2: Computer" << endl;
    cout << "Option 3) Player 1: Computer and Player 2: Computer" << endl;
    cout << "Option 4) Player 1: Computer and Player 2: Human" << endl;
    cout << "Option 5) Player 1: Human and Player 2: Smart Computer" << endl;
    cout << "Option 6) Player 1: Computer and Player 2: Smart Computer" << endl;
    cout << "Option 7) Player 1: Smart Computer and Player 2: Smart Computer" << endl;
    cout << "Option 8) Player 1: Smart Computer and Player 2: Computer" << endl;
    cout << "Option 9) Exit Game" << endl;
    cout << endl;
}

