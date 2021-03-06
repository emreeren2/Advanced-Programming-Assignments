#ifndef BOARD_H
#define BOARD_H

#include<string>
using namespace std;

class Board
{
	private:
		char theBoard[2][6]; //defining 2 by 6 char matrix

	public:
		Board(); //constructor
		void displayBoard()const; // this function will display board
		char getOwner(int, int); // this function returns which character stays in given coordinates
		void setOwner(int, int, char); // this function sets owner to given coordinates
		bool isFull() const; // controls function is full or not
		int countOwnedCells(char); // count which character has how much cell
};
#endif