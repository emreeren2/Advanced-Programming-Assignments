#include "Board.h"
#include <iostream>

using namespace std;

//constructor:
Board::Board() // set each element in matrix as '-'
{
	for(int i=0; i<2; i++){
		for(int j=0; j<6; j++){
			theBoard[i][j] = '-';
		}
	}
}

void Board::displayBoard()const // it displays board 
{
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 6; j++){
			cout << theBoard[i][j] << " ";
		}
		cout <<endl;
	}	
}

char Board::getOwner(int i, int j) // it returns the element that in given coordinates
{
	return theBoard[i][j];
}

void Board::setOwner(int i, int j, char owner) // it sets the given character in given coordinates
{
	theBoard[i][j] = owner;
}

bool Board::isFull()const // this function controls whether board is full or not
{                         // if there exist '-' in board function returns false which means board is not full, else it returns true
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (theBoard[i][j] == '-')
			{
				return false;
			}
		}
	}
	return true;
}

int Board::countOwnedCells(char owner) // this function looks how much character exists in board with given character(owner) 
{
	int counter = 0;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (theBoard[i][j] == owner)
			{
				counter++;
			}
		}
	}
	return counter;
}

