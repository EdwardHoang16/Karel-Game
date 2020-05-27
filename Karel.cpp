/*
Edward Hoang
Defines a class representing Karel.
*/

#include "Karel.h"
#include "GameBoard.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

Karel::Karel(GameBoard* pointerToGameBoard, int row, int column) {
	setPointerToGameBoard(pointerToGameBoard);
	robotLoop(pointerToGameBoard, row, column);
}

void Karel::setPointerToGameBoard(GameBoard* pointerToGameBoard) {
	this->pointerToGameBoard = pointerToGameBoard;
}

void Karel::setRow(int row) {
	this->row = row;
}

void Karel::setColumn(int column) {
	this->column = column;
}

//This function creates the "o" representing the robot.
void Karel::setUpRobot(vector<vector<char> >& gameBoardVector, int row, int column) {
	setRow(row);
	setColumn(column);
	gameBoardVector[row][column] = 'o';
}

//This function takes as input the commands for the robot.
string Karel::getInput() {
	cout << "\nHere are the inputs this robot can take:" << endl;
	cout << "move();" << endl;
	cout << "turnLeft();" << endl;
	cout << "putBeeper();" << endl;
	cout << "pickBeeper();" << endl;
	cout << "readBoard(filename)" << endl;
	cout << "writeBoard(filename)" << endl;
	cout << "Enter your command: ";

	cin >> command;
	return command;
}

//This function reads the user input command, looking for the appropriate matches.
void Karel::readInput(GameBoard* pointerToGameBoard, vector<vector<char> >& gameBoardVector, int gameBoardRows, int gameBoardColumns) {
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
	else if (readBoardCommand(pointerToGameBoard, gameBoardVector, gameBoardRows, gameBoardColumns)) {
	}
	else if (writeBoardCommand(gameBoardVector, gameBoardRows, gameBoardColumns)) {
	}
	else {
		cout << "\nSyntax Error.\n" << endl;
	}
}

//This function is responsible for the loop of taking user input and proceeding with the appropriate response.
void Karel::robotLoop(GameBoard* pointerToGameBoard, int& row, int& column) {
	keepGoing = true;
	atLeft = 0;

	setUpRobot(pointerToGameBoard->getGameBoardVector(), row, column);
	pointerToGameBoard->displayGameBoard();

	while (keepGoing == true) {
		command = getInput();
		cout << "\n";
		readInput(pointerToGameBoard, pointerToGameBoard->getGameBoardVector(), pointerToGameBoard->getGameBoardRows(), pointerToGameBoard->getGameBoardColumns());
		pointerToGameBoard->displayGameBoard();
	}
}

//This function causes the robot to move one unit right.
void Karel::moveRight(vector<vector<char> >& gameBoardVector, int& gameBoardRows, int& gameBoardColumns) {
	column++;
	if (row > gameBoardRows - 1 || row < 0 || column > gameBoardColumns - 1 || column < 0 || gameBoardVector[row][column] == '#') {
		cout << "\nKarel has crashed!\n" << endl;
		keepGoing = false;
	}
	else {
		if (gameBoardVector[row][column] != 'X') {
			gameBoardVector[row][column + storedMovement] = 'o';
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
void Karel::moveUp(vector<vector<char> >& gameBoardVector, int& gameBoardRows, int& gameBoardColumns) {
	row--;
	if (row > gameBoardRows - 1 || row < 0 || column > gameBoardColumns - 1 || column < 0 || gameBoardVector[row][column] == '#') {
		cout << "\nKarel has crashed!\n" << endl;
		keepGoing = false;
	}
	else {
		if (gameBoardVector[row][column] != 'X') {
			gameBoardVector[row - storedMovement][column] = 'o';
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
void Karel::moveLeft(vector<vector<char> >& gameBoardVector, int& gameBoardRows, int& gameBoardColumns) {
	column--;
	if (row > gameBoardRows - 1 || row < 0 || column > gameBoardColumns - 1 || column < 0 || gameBoardVector[row][column] == '#') {
		cout << "\nKarel has crashed!\n" << endl;
		keepGoing = false;
	}
	else {
		if (gameBoardVector[row][column] != 'X') {
			gameBoardVector[row][column - storedMovement] = 'o';
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
void Karel::moveDown(vector<vector<char> >& gameBoardVector, int& gameBoardRows, int& gameBoardColumns) {
	row++;
	if (row > gameBoardRows - 1 || row < 0 || column > gameBoardColumns - 1 || column < 0 || gameBoardVector[row][column] == '#') {
		cout << "\nKarel has crashed!\n" << endl;
		keepGoing = false;
	}
	else {
		if (gameBoardVector[row][column] != 'X') {
			gameBoardVector[row + storedMovement][column] = 'o';
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

//This function handles the move(); user input command. This will move the robot by one unit in a direction based on atLeft.
void Karel::moveCommand(vector<vector<char> >& gameBoardVector, int& gameBoardRows, int& gameBoardColumns) {
	storedMovement = 0;

	if (atLeft == 0) {
		moveRight(gameBoardVector, gameBoardRows, gameBoardColumns);
	}
	else if (atLeft == 1) {
		moveUp(gameBoardVector, gameBoardRows, gameBoardColumns);
	}
	else if (atLeft == 2) {
		moveLeft(gameBoardVector, gameBoardRows, gameBoardColumns);
	}
	else if (atLeft == 3) {
		moveDown(gameBoardVector, gameBoardRows, gameBoardColumns);
	}
}

//This function handles the turnLeft(); user input command. This will change the direction the robot is facing toward its left.
void Karel::turnLeftCommand() {
	atLeft++;
	if (atLeft == 1) {
		cout << "\nThe robot is facing up.\n" << endl;
	}
	else if (atLeft == 2) {
		cout << "\nThe robot is facing left.\n" << endl;
	}
	else if (atLeft == 3) {
		cout << "\nThe robot is facing down.\n" << endl;
	}
	else if (atLeft == 4) {
		atLeft = 0;
		cout << "\nThe robot is facing right.\n" << endl;
	}
}

//This function handles the putBeeper(); user input command. This will place a beeper where the robot is located.
void Karel::putBeeperCommand(vector<vector<char> >& gameBoardVector) {
	gameBoardVector[row][column] = '@';
}

//This function handles the pickBeeper(); user input command. This will pick up a beeper, or if no beeper is present where 
//the robot is located, the robot will crash.
void Karel::pickBeeperCommand(vector<vector<char> >& gameBoardVector) {
	if (gameBoardVector[row][column] == '@') {
		gameBoardVector[row][column] = 'o';
	}
	else if (gameBoardVector[row][column] != '@') {
		cout << "\nKarel has crashed!\n" << endl;
		keepGoing = false;
	}
}

//This function reads in a text file in the proper format and produces a grid from the text in the file.
bool Karel::readBoardCommand(GameBoard* pointerToGameBoard, vector<vector<char> >& gameBoardVector, int& gameBoardRows, int& gameBoardColumns) {
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

			if (symbol == 'o') {
				gameBoardVector[row][column] = 'o';
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
				if (gameBoardVector[displayRows][displayColumns] == 'o' || gameBoardVector[displayRows][displayColumns] == '@') {
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
bool Karel::writeBoardCommand(vector<vector<char> >& gameBoardVector, int gameBoardRows, int gameBoardColumns) {
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
				if (gameBoardVector[indexRows][indexColumns] == 'o') {
					int rowPositionOfKarel = indexRows;
					int columnPositionOfKarel = indexColumns;
					writeBoardFile << rowPositionOfKarel << ", " << columnPositionOfKarel << ", " << "o" << "\n";
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
					int rowPositionOfKarelAndBeeper = indexRows;
					int columnPositionOfKarelAndBeeper = indexColumns;
					writeBoardFile << rowPositionOfKarelAndBeeper << ", " << columnPositionOfKarelAndBeeper << ", " << "@" << "\n";
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