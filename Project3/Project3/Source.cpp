#include <array>
#include <iostream>

using namespace std;

template<size_t row, size_t col>
void populateWorld(char (&array)[row][col]) {

	cout << "HERE IS THE MAP FOR CHOOSING A SPACE \n" << endl;
	char counter = '1';

	for (int r = 0; r < row; r++) {

		for (int c = 0; c < col; c++) {

			array[r][c] = counter;
			counter++;

			cout << array[r][c] << "\t";

		}

		cout << "\n" << endl;

	}

	cout << "----------------------------------------" << endl;

	for (int r = 0; r < row; r++) {

		for (int c = 0; c < col; c++) {

			array[r][c] = '.';

			cout << array[r][c] << "\t";

		}

		cout << "\n" << endl;

	}

}

template<size_t row, size_t col>
void updateWorld(char (&array)[row][col], int space, bool turn) {

	if (turn) {
		switch (space) {
			case 1:
				array[0][0] = 'X';
				break;
			case 2:
				array[0][1] = 'X';
				break;
			case 3:
				array[0][2] = 'X';
				break;
			case 4:
				array[1][0] = 'X';
				break;
			case 5:
				array[1][1] = 'X';
				break;
			case 6:
				array[1][2] = 'X';
				break;
			case 7:
				array[2][0] = 'X';
				break;
			case 8:
				array[2][1] = 'X';
				break;
			case 9:
				array[2][2] = 'X';
				break;
			default:
				cout << "INVALID OPTION" << endl;
				break;
		}
	}
	else {
		switch (space) {
			case 1:
				array[0][0] = 'O';
				break;
			case 2:
				array[0][1] = 'O';
				break;
			case 3:
				array[0][2] = 'O';
				break;
			case 4:
				array[1][0] = 'O';
				break;
			case 5:
				array[1][1] = 'O';
				break;
			case 6:
				array[1][2] = 'O';
				break;
			case 7:
				array[2][0] = 'O';
				break;
			case 8:
				array[2][1] = 'O';
				break;
			case 9:
				array[2][2] = 'O';
				break;
			default:
				cout << "INVALID OPTION" << endl;
				break;
		}
	}

	for (int r = 0; r < row; r++) {

		for (int c = 0; c < col; c++) {

			cout << array[r][c] << "\t";

		}

		cout << "\n" << endl;

	}

}

template <size_t row, size_t col>
bool checkForWin(char (&array)[row][col]) {

	if (array[0][0] == array[0][1] && array[0][0] == array[0][2] && array[0][0] != '.')
		return true;
	else if (array[1][0] == array[1][1] && array[1][0] == array[1][2] && array[1][0] != '.')
		return true;
	else if (array[2][0] == array[2][1] && array[2][0] == array[2][2] && array[2][1] != '.')
		return true;

	else if (array[0][0] == array[1][0] && array[0][0] == array[2][0] && array[0][0] != '.')
		return true;
	else if (array[0][1] == array[1][1] && array[0][1] == array[2][1] && array[0][1] != '.')
		return true;
	else if (array[0][2] == array[1][2] && array[0][2] == array[2][2] && array[0][2] != '.')
		return true;

	else if (array[0][0] == array[1][1] && array[0][0] == array[2][2] && array[0][0] != '.')
		return true;
	else if (array[0][2] == array[1][1] && array[0][2] == array[2][0] && array[0][2] != '.')
		return true;

	else
		return false;

}


int main() {

	char world[3][3];

	bool whosTurn = true;
	bool winCon = false;

	int locX;
	int locO;

	populateWorld(world);

	
	while (!winCon) {

		cout << "----------------------------------------" << endl;
		cout << "CHOOSE A LOCATION TO PLAY";

		if (whosTurn) {

			cout << "(X)" << endl;
			cin >> locX;
			cout << "\n";
			updateWorld(world, locX, whosTurn);
			whosTurn = false;

		}
		else {

			cout << "(O)" << endl;
			cin >> locO;
			cout << "\n";
			updateWorld(world, locO, whosTurn);
			whosTurn = true;
		}

		winCon = (checkForWin(world));

		if (winCon && whosTurn)
			cout << "O WINS" << endl;
		else if (winCon)
			cout << "X WINS" << endl;


	}


}
