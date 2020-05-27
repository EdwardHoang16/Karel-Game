/*
Edward Hoang
The question this code responds to is one asking for classes representing a game board, Karel, and SuperKarel.
Karel can move, turn left, put a beeper down, and pick a beeper up. SuperKarel can move, turn left, put a beeper down,
pick a beeper up, turn right, and repeat a command a number of times. Karel and SuperKarel can also now load and store
board states using readBoard(filename); and writeBoard(filename);.
Declares a class representing a game board. The GameBoard class creates a vector of a character vector which forms a
two-dimensional game board for Karel and SuperKarel to act upon.
*/

#pragma once

#include <vector>

class GameBoard {
private:
	int gameBoardRows;
	int gameBoardColumns;
	std::vector<std::vector<char> > gameBoardVector;

public:
	GameBoard();

	GameBoard(int gameBoardRows, int gameBoardColumns);

	int& getGameBoardRows();
	int& getGameBoardColumns();
	std::vector<std::vector<char> >& getGameBoardVector();

	void setUpBoard(int gameBoardRows, int gameBoardColumns);

	void displayGameBoard() const;
};