#include "Player.h"
#include <iostream>

using namespace std;

//constructor:
Player::Player( Board & board, const char & id, const int & dir)
	: myBoard(board), playerId(id), playerDir(dir)
{ row = 0; col = 0; }

void Player::move(int distance)
{
	int j = col;
	int i = row;
	int counter = 0;

	if (playerDir == 1) // if player A move (clockwise)
	{
		while (counter != distance) // while it does not complete its progression
		{
			if (i == 0) // if it stays in the first row
			{
				while (j < 5 && counter != distance) // increment current position while it reaches to end of the row or it completes its progression, 
				{                                    // moreover, if counter reaches given distance it stops the progress
					j++;
					counter++;
				}

				if (counter != distance) // if it reaches the end of the row and it still has to move
				{                        // it goes to second row
					i++;
					counter++;
				}
			}
			else // if it stays in the second row
			{
				while (j > 0 && counter != distance)  // decrement current position while it reaches to beggining of the row or it completes its progression, 
				{                                     // moreover, if counter reaches given distance it stops the progress
					j--;
					counter++;
				}

				if (counter != distance) // if it reaches the end of the row and it still has to move
				{                        // it goes to first row
					i--;
					counter++;
				}
			}
		}
		row = i;
		col = j;
	}

	else // if player B move (counter-clockwise)
	{
		while (counter != distance) // while it does not complete its progression
		{
			if (i == 0) // if it stays in the first row 
			{
				while (j > 0 && counter != distance) // decrement current position while it reaches to beggining of the row or it completes its progression, 
				{                                    // moreover, if counter reaches given distance it stops the progress
					j--;
					counter++;
				}

				if (counter != distance) // if it reaches the beggining of the row and it still has to move
				{                        // it goes to first row
					i++;
					counter++;
				}
			}
			else // if it stays in the second row
			{
				while (j < 5 && counter != distance) // increment current position while it reaches to end of the row or it completes its progression, 
				{                                    // moreover, if counter reaches given distance it stops the progression
					j++;
					counter++;
				}

				if (counter != distance) // if it reaches the end of the row and it still has to move
				{                        // it goes to first row 
					i--;
					counter++;
				}
			}
		}
		row = i;
		col = j;
	}
}

void Player::claimOwnership() // if current cell is empty, this function sets empty cell as a player ID that whose call this function
{
	if (myBoard.getOwner(row, col) == '-' )
	{
		myBoard.setOwner(row, col, playerId);
	}
}

bool Player::wins() // if a player has more than 6 cell, it will win the game.
{                   // this function returns true when player has more than 6 cells which means it win the game, else it returns false
	if (myBoard.countOwnedCells(playerId) > 6)
		return true;
	else
		return false;
}

int Player::getRow() // this function returns the row
{
	return row;
}

int Player::getCol() // this function returns the column
{
	return col;
}

