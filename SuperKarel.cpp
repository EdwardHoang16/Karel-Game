/*
Edward Hoang
Defines a class representing SuperKarel.
*/

#include "SuperKarel.h"
#include "GameBoard.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;

SuperKarel::SuperKarel(GameBoard* pointerToGameBoard, int row, int column) {
	setPointerToGameBoard(pointerToGameBoard);
	robotLoop(pointerToGameBoard, row, column);
}

void SuperKarel::setPointerToGameBoard(GameBoard* pointerToGameBoard) {
	this->pointerToGameBoard = pointerToGameBoard;
}

void SuperKarel::setRow(int row) {
	this->row = row;
}

void SuperKarel::setColumn(int column) {
	this->column = column;
}

//This function creates the "O" representing the robot.
void SuperKarel::setUpRobot(vector<vector<char> >& gameBoardVector, int row, int column) {
	setRow(row);
	setColumn(column);
	gameBoardVector[row][column] = 'O';
}

//This function takes as input the commands for the robot.
string SuperKarel::getInput() {
	cout << "\nHere are the inputs this robot can take:" << endl;
	cout << "move();" << endl;
	cout << "turnLeft();" << endl;
	cout << "putBeeper();" << endl;
	cout << "pickBeeper();" << endl;
	cout << "turnRight();" << endl;
	cout << "repeat(n);" << endl;
	cout << "readBoard(filename)" << endl;
	cout << "writeBoard(filename)" << endl;
	cout << "Enter your command: ";

	cin >> command;
	return command;
}

//This function reads the user input command, looking for the appropriate matches.
void SuperKarel::readInput(GameBoard* pointerToGameBoard, vector<vector<char> >& gameBoardVector, int gameBoardRows, int gameBoardColumns) {
	if (command == "move();") {
		moveCommand(gameBoardVector, gameBoardRows, gameBoardColumns);
	}
	else if (command == "turnLeft();") {
		turnLeftCommand();
	}
	else if (command == "putBeeper();") {
		putBeeperCommand(gameBoardVector);
	}
	else if (command == "pickBeeper();") {
		pickBeeperCommand(gameBoardVector);
	}
	else if (command == "turnRight();") {
		turnRightCommand();
	}
	else if (repeatCommand()) {
	}
	else if (readBoardCommand(pointerToGameBoard, gameBoardVector, gameBoardRows, gameBoardColumns)) {
	}
	else if (writeBoardCommand(gameBoardVector, gameBoardRows, gameBoardColumns)) {
	}
	else {
		cout << "\nSyntax Error.\n" << endl;
	}
}

//This function is responsible for the loop of taking user input and proceeding with the appropriate response.
void SuperKarel::robotLoop(GameBoard* pointerToGameBoard, int& row, int& column) {
	keepGoing = true;
	atLeft = 0;
	atRight = 0;
	numberOfRepetitions = 0;

	setUpRobot(pointerToGameBoard->getGameBoardVector(), row, column);
	pointerToGameBoard->displayGameBoard();

	while (keepGoing == true) {
		command = getInput();
		cout << "\n";
		readInput(pointerToGameBoard, pointerToGameBoard->getGameBoardVector(), pointerToGameBoard->getGameBoardRows(), pointerToGameBoard->getGameBoardColumns());
		pointerToGameBoard->displayGameBoard();
	}
}

//This function calculates the true direction the robot is facing, considering both atLeft and atRight.
void SuperKarel::calculateDirection(int& atLeft, int& atRight) {
	if ((atRight - atLeft) > 0) {
		atRight = abs(atRight - atLeft);
		atLeft = 0;
	}
	else if ((atRight - atLeft) < 0) {
		atLeft = abs(atRight - atLeft);
		atRight = 0;
	}
	else if ((atRight - atLeft) == 0) {
		atLeft = 0;
		atRight = 0;
	}

	if (atLeft == 0 && atRight == 0) {
		cout << "\nThe robot is facing right.\n" << endl;
	}
	else if (atLeft == 1 || atRight == 3) {
		cout << "\nThe robot is facing up.\n" << endl;
	}
	else if (atLeft == 2 || atRight == 2) {
		cout << "\nThe robot is facing left.\n" << endl;
	}
	else if (atLeft == 3 || atRight == 1) {
		cout << "\nThe robot is facing down.\n" << endl;
	}
	else if (atLeft == 4 || atRight == 4) {
		if (atLeft == 4) {
			atLeft = 0;
		}
		else if (atRight == 4) {
			atRight = 0;
		}
		cout << "\nThe robot is facing right.\n" << endl;
	}
}

//This function causes the robot to move one unit right.
void SuperKarel::moveRight(vector<vector<char> >& gameBoardVector, int& gameBoardRows, int& gameBoardColumns) {
	column++;
	if (row > gameBoardRows - 1 || row < 0 || column > gameBoardColumns - 1 || column < 0 || gameBoardVector[row][column] == '#') {
		cout << "\nKarel has crashed!\n" << endl;
		keepGoing = false;
	}
	else {
		if (gameBoardVector[row][column] != 'X') {
			gameBoardVector[row][column + storedMovement] = 'O';
			storedMovement = 0;
		}
		else {
			storedMovement++;
			gameBoardVector[row][column] = '@';
		}
		if (gameBoardVector[row][column - 1] == 'X' || gameBoardVector[row][column - 1] == '@') {
			gameBoardVector[row][column - 1] = 'X';
		}
		else {
			gameBoardVector[row][column - 1] = '-';
		}
	}
}

//This function causes the robot to move one unit up.
void SuperKarel::moveUp(vector<vector<char> >& gameBoardVector, int& gameBoardRows, int& gameBoardColumns) {
	row--;
	if (row > gameBoardRows - 1 || row < 0 || column > gameBoardColumns - 1 || column < 0 || gameBoardVector[row][column] == '#') {
		cout << "\nKarel has crashed!\n" << endl;
		keepGoing = false;
	}
	else {
		if (gameBoardVector[row][column] != 'X') {
			gameBoardVector[row - storedMovement][column] = 'O';
			storedMovement = 0;
		}
		else {
			storedMovement++;
			gameBoardVector[row][column] = '@';
		}
		if (gameBoardVector[row + 1][column] == 'X' || gameBoardVector[row + 1][column] == '@') {
			gameBoardVector[row + 1][column] = 'X';
		}
		else {
			gameBoardVector[row + 1][column] = '-';
		}
	}
}

//This function causes the robot to move one unit left.
void SuperKarel::moveLeft(vector<vector<char> >& gameBoardVector, int& gameBoardRows, int& gameBoardColumns) {
	column--;
	if (row > gameBoardRows - 1 || row < 0 || column > gameBoardColumns - 1 || column < 0 || gameBoardVector[row][column] == '#') {
		cout << "\nKarel has crashed!\n" << endl;
		keepGoing = false;
	}
	else {
		if (gameBoardVector[row][column] != 'X') {
			gameBoardVector[row][column - storedMovement] = 'O';
			storedMovement = 0;
		}
		else {
			storedMovement++;
			gameBoardVector[row][column] = '@';
		}
		if (gameBoardVector[row][column + 1] == 'X' || gameBoardVector[row][column + 1] == '@') {
			gameBoardVector[row][column + 1] = 'X';
		}
		else {
			gameBoardVector[row][column + 1] = '-';
		}
	}
}

//This function causes the robot to move one unit down.
void SuperKarel::moveDown(vector<vector<char> >& gameBoardVector, int& gameBoardRows, int& gameBoardColumns) {
	row++;
	if (row > gameBoardRows - 1 || row < 0 || column > gameBoardColumns - 1 || column < 0 || gameBoardVector[row][column] == '#') {
		cout << "\nKarel has crashed!\n" << endl;
		keepGoing = false;
	}
	else {
		if (gameBoardVector[row][column] != 'X') {
			gameBoardVector[row + storedMovement][column] = 'O';
			storedMovement = 0;
		}
		else {
			storedMovement++;
			gameBoardVector[row][column] = '@';
		}
		if (gameBoardVector[row - 1][column] == 'X' || gameBoardVector[row - 1][column] == '@') {
			gameBoardVector[row - 1][column] = 'X';
		}
		else {
			gameBoardVector[row - 1][column] = '-';
		}
	}
}

//This function handles the move(); user input command. This will move the robot by one unit in a direction based on atLeft, atRight, or both.
void SuperKarel::moveCommand(vector<vector<char> >& gameBoardVector, int& gameBoardRows, int& gameBoardColumns) {
	while (numberOfRepetitions >= 0) {
		storedMovement = 0;

		if (atLeft == 0 && atRight == 0) {
			moveRight(gameBoardVector, gameBoardRows, gameBoardColumns);
		}
		else if (atLeft == 1 || atRight == 3) {
			moveUp(gameBoardVector, gameBoardRows, gameBoardColumns);
		}
		else if (atLeft == 2 || atRight == 2) {
			moveLeft(gameBoardVector, gameBoardRows, gameBoardColumns);
		}
		else if (atLeft == 3 || atRight == 1) {
			moveDown(gameBoardVector, gameBoardRows, gameBoardColumns);
		}

		numberOfRepetitions--;
	}

	if (numberOfRepetitions < 0) {
		numberOfRepetitions = 0;
	}
}

//This function handles the turnLeft(); user input command. This will changes the direction the robot is facing toward its left.
void SuperKarel::turnLeftCommand() {
	while (numberOfRepetitions >= 0) {
		atLeft++;
		calculateDirection(atLeft, atRight);
		numberOfRepetitions--;
	}

	if (numberOfRepetitions < 0) {
		numberOfRepetitions = 0;
	}
}

//This function handles the putBeeper(); user input command. This will place a beeper where the robot is located.
void SuperKarel::putBeeperCommand(vector<vector<char> >& gameBoardVector) {
	while (numberOfRepetitions >= 0) {
		gameBoardVector[row][column] = '@';
		numberOfRepetitions--;
	}

	if (numberOfRepetitions < 0) {
		numberOfRepetitions = 0;
	}
}

//This function handles the pickBeeper(); user input command. This will pick up a beeper, or if no beeper is present where 
//the robot is located, the robot will crash.
void SuperKarel::pickBeeperCommand(vector<vector<char> >& gameBoardVector) {
	while (numberOfRepetitions >= 0) {
		if (gameBoardVector[row][column] == '@') {
			gameBoardVector[row][column] = 'O';
		}
		else if (gameBoardVector[row][column] != '@') {
			cout << "\nKarel has crashed!\n" << endl;
			keepGoing = false;
		}
		numberOfRepetitions--;
	}

	if (numberOfRepetitions < 0) {
		numberOfRepetitions = 0;
	}
}

//This function handles the turnRight(); user input command. This will change the direction the robot is facing toward its right.
void SuperKarel::turnRightCommand() {
	while (numberOfRepetitions >= 0) {
		atRight++;
		calculateDirection(atLeft, atRight);
		numberOfRepetitions--;
	}

	if (numberOfRepetitions < 0) {
		numberOfRepetitions = 0;
	}
}

//If n is a positive nonzero integer, this function will have the robot repeat the next single command the user enters a number of times equal to the value of n.
bool SuperKarel::repeatCommand() {
	string validInputBeforeInt = "repeat(";
	char validInputAfterInt1 = ')';
	char validInputAfterInt2 = ';';
	char invalidChar;

	if (command.find(validInputBeforeInt) != string::npos) {
		int locationOfLastChar = command.length() - 1;
		int locationOfSecondLastChar = command.length() - 2;
		if ((command.at(locationOfSecondLastChar) == validInputAfterInt1) && (command.at(locationOfLastChar) == validInputAfterInt2)) {
			command.erase(locationOfSecondLastChar, 2);

			string unprocessedNumberOfRepetitions = command.substr(7, 10);
			stringstream stringStream(unprocessedNumberOfRepetitions);
			stringStream >> numberOfRepetitions;

			if (stringStream.fail() || stringStream.get(invalidChar) || numberOfRepetitions < 0) {
				return false;
			}

			return true;
		}
	}
	return false;
}

//This function reads in a text file in the proper format and produces a grid from the text in the file.
bool SuperKarel::readBoardCommand(GameBoard* pointerToGameBoard, vector<vector<char> >& gameBoardVector, int& gameBoardRows, int& gameBoardColumns) {
	const string validInputBeforeTextFile = "readBoard(";
	const char validInputAfterTextFile1 = ')';
	const char validInputAfterTextFile2 = ';';

	if (command.find(validInputBeforeTextFile) != string::npos) {
		string firstUnprocessed;
		string secondUnprocessed;
		string thirdUnprocessed;

		string textFileUnprocessed = command.substr(10, string::npos);
		string textFileProcessed = textFileUnprocessed.erase(textFileUnprocessed.length() - 2, 2);

		ifstream readBoardFile;
		readBoardFile.open(textFileProcessed);

		readBoardFile >> gameBoardRows;
		readBoardFile >> gameBoardColumns;
		pointerToGameBoard->setUpBoard(gameBoardRows, gameBoardColumns);

		while (readBoardFile >> firstUnprocessed >> secondUnprocessed >> thirdUnprocessed) {
			string firstProcessed = firstUnprocessed.erase(firstUnprocessed.length() - 1, 1);
			string secondProcessed = secondUnprocessed.erase(secondUnprocessed.length() - 1, 1);
			char symbol = thirdUnprocessed.front();

			int row = stoi(firstProcessed);
			int column = stoi(secondProcessed);

			if (symbol == 'O') {
				gameBoardVector[row][column] = 'O';
			}
			if (symbol == 'X') {
				gameBoardVector[row][column] = 'X';
			}
			if (symbol == '#') {
				gameBoardVector[row][column] = '#';
			}
			if (symbol == '@') {
				gameBoardVector[row][column] = '@';
			}
		}

		for (unsigned int displayRows = 0; displayRows < gameBoardVector.size(); ++displayRows) {
			for (unsigned int displayColumns = 0; displayColumns < gameBoardVector[displayRows].size(); ++displayColumns) {
				if (gameBoardVector[displayRows][displayColumns] == 'O' || gameBoardVector[displayRows][displayColumns] == '@') {
					row = displayRows;
					column = displayColumns;
				}
			}
		}

		if ((command.at(command.length() - 2) == validInputAfterTextFile1) && (command.at(command.length() - 1) == validInputAfterTextFile2)) {
			readBoardFile.close();
			return true;
		}
	}
	return false;
}

//This function writes the current state of the board in the proper format.
bool SuperKarel::writeBoardCommand(vector<vector<char> >& gameBoardVector, int gameBoardRows, int gameBoardColumns) {
	const string validInputBeforeTextFile = "writeBoard(";
	const char validInputAfterTextFile1 = ')';
	const char validInputAfterTextFile2 = ';';

	if (command.find(validInputBeforeTextFile) != string::npos) {
		string textFileUnprocessed = command.substr(11, string::npos);
		string textFileProcessed = textFileUnprocessed.erase(textFileUnprocessed.length() - 2, 2);
		ofstream writeBoardFile;
		writeBoardFile.open(textFileProcessed);

		writeBoardFile << gameBoardRows << "\n" << gameBoardColumns << "\n";

		for (unsigned int indexRows = 0; indexRows < gameBoardVector.size(); ++indexRows) {
			for (unsigned int indexColumns = 0; indexColumns < gameBoardVector[indexRows].size(); ++indexColumns) {
				if (gameBoardVector[indexRows][indexColumns] == 'O') {
					int rowPositionOfSuperKarel = indexRows;
					int columnPositionOfSuperKarel = indexColumns;
					writeBoardFile << rowPositionOfSuperKarel << ", " << columnPositionOfSuperKarel << ", " << "O" << "\n";
				}
				else if (gameBoardVector[indexRows][indexColumns] == 'X') {
					int rowPositionOfBeeper = indexRows;
					int columnPositionOfBeeper = indexColumns;
					writeBoardFile << rowPositionOfBeeper << ", " << columnPositionOfBeeper << ", " << "X" << "\n";
				}
				else if (gameBoardVector[indexRows][indexColumns] == '#') {
					int rowPositionOfWall = indexRows;
					int columnPositionOfWall = indexColumns;
					writeBoardFile << rowPositionOfWall << ", " << columnPositionOfWall << ", " << "#" << "\n";
				}
				else if (gameBoardVector[indexRows][indexColumns] == '@') {
					int rowPositionOfSuperKarelAndBeeper = indexRows;
					int columnPositionOfSuperKarelAndBeeper = indexColumns;
					writeBoardFile << rowPositionOfSuperKarelAndBeeper << ", " << columnPositionOfSuperKarelAndBeeper << ", " << "@" << "\n";
				}
			}
		}

		if ((command.at(command.length() - 2) == validInputAfterTextFile1) && (command.at(command.length() - 1) == validInputAfterTextFile2)) {
			writeBoardFile.close();
			return true;
		}
	}
	return false;
}