#include "Functions.h"

void runGame()
{

	int x, y, turn;
	char board[3][3];
	bool draw = false;

	bool stillPlaying = true;
	bool replaying = true;
	char playAgain;

	while (stillPlaying) {

		initBoard(board);
		turn = 0;
		draw = false;

		while (replaying && (!checkForWinner('X', board) && !checkForWinner('O', board) && !draw)) {


			if (turn == 0 || turn % 2 == 0)
				cout << "Enter coordinate for X. Input should be X Y" << endl;
			else
				cout << "Enter coordinate for O. Input should be X Y" << endl;

			cin >> x >> y;

			if (turn == 0 || turn % 2 == 0)
				placeAPiece(x, y, 'X', board);

			else
				placeAPiece(x, y, 'O', board);

			displayBoard(board);

			turn++;

			if (turn >= 9)
				draw = checkForDraw(board);

		}


		if (checkForWinner('X', board))
			cout << "X Won" << endl;
		else if (checkForWinner('O', board))
			cout << "O Won" << endl;
		else
			cout << "Draw" << endl;


		cout << "Do you want to play again?" << endl;

		cin >> playAgain;

		if (playAgain == 'y' || playAgain == 'Y') {
			stillPlaying = true;
			replaying = true;
		}
		if (playAgain == 'n' || playAgain == 'N') {
			stillPlaying = false;
			replaying = false;
		}

	}

	cout << "Done" << endl;

}

void initBoard(char board[3][3])
{
	
	for (int t = 0; t < 3; t++) {

		for (int v = 0; v < 3; v++) {

			board[t][v] = '-';

		}

	}

}

void placeAPiece(int x, int y, char piece, char board[3][3])
{
	board[x][y] = piece;

}

bool checkForWinner(char piece, char board[3][3])
{
	int score = 0;

	
	if (piece == 'X') {

		for (int j = 0; j < 3; j++) {			//Check for a win on each row

			for (int s = 0; s < 3; s++) {

				if(board[j][s] == piece)
					score += 1;

			}

			if (score == 3) {
				return true;
			}

			score = 0;

		}

		for (int j = 0; j < 3; j++) {			//Check for a win on each col

			for (int s = 0; s < 3; s++) {

				if (board[s][j] == piece)
					score += 1;

			}

			if (score == 3)
				return true;

			score = 0;

		}

		for (int j = 0; j < 3; j++) {			//Check for win in left-right diagonal

			if (board[j][j] == piece)
				score += 1;

			if (score == 3)
				return true;
		}

	}

	if (piece == 'O') {

		for (int d = 0; d < 3; d++) {			//Check for a win on each row

			for (int n = 0; n < 3; n++) {

				if (board[d][n] == piece)
					score += 1;


			}

			if (score == 3)
				return true;

			score = 0;

		}

		for (int d = 0; d < 3; d++) {			//Check for a win on each col

			for (int n = 0; n < 3; n++) {

				if (board[n][d] == piece)
					score += 1;

			}

			if (score == 3)
				return true;

			score = 0;

		}

		for (int d = 0; d < 3; d++) {			//Check for win in left-right diagonal

			if (board[d][d] == piece)
				score += 1;

			if (score == 3)
				return true;
		}

	}

	return false;
}

bool checkForDraw(char board[3][3])
{

	int emptySpaces = 0;

	for (int t = 0; t < 3; t++) {

		for (int b = 0; b < 3; b++) {

			if (board[t][b] == '-')
				emptySpaces++;

			//cout << "Empty Spaces: " << emptySpaces << endl;

		}

	}

	if (!checkForWinner('X', board) && !checkForWinner('O', board) && emptySpaces == 0) {

		return true;

	}

	return false;
}


void displayBoard(char board[3][3])
{

	int spacers = 0;
	int dashes = 0;

	for (int a = 0; a < 3; a++) {

		for (int b = 0; b < 3; b++) {

			cout << board[a][b];

			if (spacers < 2)
				cout << '|';
		
			spacers++;

		}

		cout << endl;

		if(dashes < 2)
			cout << "-----" << endl;
		
		dashes++;


		spacers = 0;

	}

	//cout << endl;

}