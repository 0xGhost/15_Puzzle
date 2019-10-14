// author: Yiang Lu
// Date created: 13/Oct/2019
#pragma once
#include "Board.h"

struct ContinuousNumber
{
	int column = 0;
	int row = 0;
	int columnReverse = 0;
	int rowReverse = 0;
	inline bool operator==(const ContinuousNumber& rhs) const
	{
		return column == rhs.column
			&& row == rhs.row
			&& columnReverse == rhs.columnReverse
			&& rowReverse == rhs.rowReverse;
	}
};


class NCLBoard :
	public Board
{
public:
	NCLBoard(const int& size, const int& min, const int& max) :Board(size, min, max) {}
	NCLBoard(const int& size, int* input);
	//~NCLBoard();
	bool IsTurnEnd(); // check if this board is a turn end 
	ContinuousNumber* CheckContinuous(); // check full continuous in all directions
	ContinuousNumber* CheckContinuous(int length); // check partial continuous in all directions

private:

};

