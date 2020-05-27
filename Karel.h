/*
Edward Hoang
The question this code responds to is one asking for classes representing a game board, Karel, and SuperKarel.
Karel can move, turn left, put a beeper down, and pick a beeper up. SuperKarel can move, turn left, put a beeper down,
pick a beeper up, turn right, and repeat a command a number of times. Karel and SuperKarel can also now load and store
board states using readBoard(filename); and writeBoard(filename);.
Declares a class representing Karel. The Karel class contains the basic functionalities of Karel, which are to move, to turn
left, to put a beeper, and to pick up a beeper. This version of Karel can also read and write to a text file.
*/

#pragma once

#include "GameBoard.h"
#include <string>
#include <vector>

class Karel {
private:
	GameBoard* pointerToGameBoard;
	bool keepGoing;
	int row;
	int column;
	int storedMovement;
	char symbol;
	int atLeft;
	std::string command;

public:
	Karel(GameBoard* pointerToGameBoard, int row, int column);

	void setPointerToGameBoard(GameBoard* pointerToGameBoard);
	void setRow(int row);
	void setColumn(int column);
	void setUpRobot(std::vector<std::vector<char> >& gameBoardVector, int row, int column);
	std::string getInput();
	void readInput(GameBoard* pointerToGameBoard, std::vector<std::vector<char> >& gameBoardVector, int gameBoardRows, int gameBoardColumns);
	void robotLoop(GameBoard* pointerToGameBoard, int& row, int& column);
	void moveRight(std::vector<std::vector<char> >& gameBoardVector, int& gameBoardRows, int& gameBoardColumns);
	void moveUp(std::vector<std::vector<char> >& gameBoardVector, int& gameBoardRows, int& gameBoardColumns);
	void moveLeft(std::vector<std::vector<char> >& gameBoardVector, int& gameBoardRows, int& gameBoardColumns);
	void moveDown(std::vector<std::vector<char> >& gameBoardVector, int& gameBoardRows, int& gameBoardColumns);

	void moveCommand(std::vector<std::vector<char> >& gameBoardVector, int& gameBoardRows, int& gameBoardColumns);
	void turnLeftCommand();
	void putBeeperCommand(std::vector<std::vector<char> >& gameBoardVector);
	void pickBeeperCommand(std::vector<std::vector<char> >& gameBoardVector);
	bool readBoardCommand(GameBoard* pointerToGameBoard, std::vector<std::vector<char> >& gameBoardVector, int& gameBoardRows, int& gameBoardColumns);
	bool writeBoardCommand(std::vector<std::vector<char> >& gameBoardVector, int gameBoardRows, int gameBoardColumns);
};