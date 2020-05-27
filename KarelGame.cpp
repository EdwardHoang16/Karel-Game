/*
Edward Hoang
The question this code responds to is one asking for classes representing a game board, Karel, and SuperKarel.
Karel can move, turn left, put a beeper down, and pick a beeper up. SuperKarel can move, turn left, put a beeper down,
pick a beeper up, turn right, and repeat a command a number of times. Karel and SuperKarel can also load and store
board states using readBoard(filename) and writeBoard(filename).
This program tests Karel and SuperKarel on a 15x15 game board with their initial positions being on the bottom left.
*/

#include <iostream>
#include "GameBoard.h"
#include "Karel.h"
#include "SuperKarel.h"

using namespace std;

int main()
{
	GameBoard gameBoardObjForKarel(15, 15);
	GameBoard gameBoardObjForSuperKarel(15, 15);

	GameBoard* pointerToGameBoardForKarel = &gameBoardObjForKarel;
	GameBoard* pointerToGameBoardForSuperKarel = &gameBoardObjForSuperKarel;

	Karel karelObj(pointerToGameBoardForKarel, 14, 0);
	cout << endl;
	SuperKarel superKarelObj(pointerToGameBoardForSuperKarel, 14, 0);
}