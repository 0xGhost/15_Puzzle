// author: Yiang Lu
// Date created: 13/Oct/2019
#pragma once
#include "Board.h"
class TurnBoard :
	public Board
{
public:
	TurnBoard(const int& size, const int& min, const int& max) :Board(size, min, max) {};
	TurnBoard(const int& size, int* input) :Board(size, input) {};
	~TurnBoard();
	bool IsTurnEnd(); // check if this board is a turn end 
	void CheckContinuous(); // check full continuous in all directions
	void CheckContinuous(int length); // check partial continuous in all directions

};

