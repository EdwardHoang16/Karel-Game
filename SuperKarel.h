/*
Edward Hoang
The question this code responds to is one asking for classes representing a game board, Karel, and SuperKarel.
Karel can move, turn left, put a beeper down, and pick a beeper up. SuperKarel can move, turn left, put a beeper down,
pick a beeper up, turn right, and repeat a command a number of times. Karel and SuperKarel can also now load and store
board states using readBoard(filename); and writeBoard(filename);.
Declares a class representing SuperKarel. The SuperKarel class contains the functionalities of the Karel class, but this
version can also turn right and repeat commands a number of times as specified by the user. Of course, SuperKarel can also
read and write to a text file.
*/

#pragma once

#include "GameBoard.h"
#include <iostream>
#include <string>
#include <vector>

class SuperKarel {
private:
	GameBoard* pointerToGameBoard;
	bool keepGoing;
	int row;
	int column;
	int storedMovement;
	char symbol;
	int atLeft;
	int atRight;
	int numberOfRepetitions;
	std::string command;

public:
	SuperKarel(GameBoard* pointerToGameBoard, int row, int column);

	void setPointerToGameBoard(GameBoard* pointerToGameBoard);
	void setRow(int row);
	void setColumn(int column);
	void setUpRobot(std::vector<std::vector<char> >& gameBoardVector, int row, int column);
	std::string getInput();
	void readInput(GameBoard* pointerToGameBoard, std::vector<std::vector<char> >& gameBoardVector, int gameBoardRows, int gameBoardColumns);
	void robotLoop(GameBoard* pointerToGameBoard, int& row, int& column);
	void calculateDirection(int& atLeft, int& atRight);
	void moveRight(std::vector<std::vector<char> >& gameBoardVector, int& gameBoardRows, int& gameBoardColumns);
	void moveUp(std::vector<std::vector<char> >& gameBoardVector, int& gameBoardRows, int& gameBoardColumns);
	void moveLeft(std::vector<std::vector<char> >& gameBoardVector, int& gameBoardRows, int& gameBoardColumns);
	void moveDown(std::vector<std::vector<char> >& gameBoardVector, int& gameBoardRows, int& gameBoardColumns);

	void moveCommand(std::vector<std::vector<char> >& gameBoardVector, int& gameBoardRows, int& gameBoardColumns);
	void putBeeperCommand(std::vector<std::vector<char> >& gameBoardVector);
	void pickBeeperCommand(std::vector<std::vector<char> >& gameBoardVector);
	void turnLeftCommand();
	void turnRightCommand();
	bool repeatCommand();
	bool readBoardCommand(GameBoard* pointerToGameBoard, std::vector<std::vector<char> >& gameBoardVector, int& gameBoardRows, int& gameBoardColumns);
	bool writeBoardCommand(std::vector<std::vector<char> >& gameBoardVector, int gameBoardRows, int gameBoardColumns);
};