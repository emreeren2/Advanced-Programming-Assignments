#ifndef PLAYER_H
#define PLAYER_H
#include "Board.h"
#include<string>
#include<iostream>
using namespace std;

class Player
{	
	private:
		char playerId;
		int row, col;
		int playerDir;
		Board & myBoard;

	public:
		Player(Board &, const char&, const int&);
		void move(int);
		void claimOwnership();
		bool wins();
		int getRow();
		int getCol(); 
};
#endif