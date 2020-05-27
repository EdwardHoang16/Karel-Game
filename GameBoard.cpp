/*
Edward Hoang
Defines a class representing a game board.
*/

#include "GameBoard.h"
#include <iostream>
#include <vector>

using namespace std;

GameBoard::GameBoard() {
	gameBoardRows = 15;
	gameBoardColumns = 15;
	setUpBoard(gameBoardRows, gameBoardColumns);
}

GameBoard::GameBoard(int gameBoardRows, int gameBoardColumns) {
	setUpBoard(gameBoardRows, gameBoardColumns);
}

int& GameBoard::getGameBoardRows() {
	return gameBoardRows;
}

int& GameBoard::getGameBoardColumns() {
	return gameBoardColumns;
}

vector<vector<char> >& GameBoard::getGameBoardVector() {
	return gameBoardVector;
}

//This function creates the vector of a character vector.
void GameBoard::setUpBoard(int gameBoardRows, int gameBoardColumns) {
	this->gameBoardRows = gameBoardRows;
	this->gameBoardColumns = gameBoardColumns;

	vector<vector<char> > gameBoardVector(gameBoardRows, vector<char>(gameBoardColumns, '-'));
	this->gameBoardVector = gameBoardVector;
}

//This function displays the current state of the game board.
void GameBoard::displayGameBoard() const {
	for (unsigned int displayRows = 0; displayRows < gameBoardVector.size(); ++displayRows) {
		for (unsigned int displayColumns = 0; displayColumns < gameBoardVector[displayRows].size(); ++displayColumns) {
			cout << gameBoardVector[displayRows][displayColumns];
		}
		cout << endl;
	}
}