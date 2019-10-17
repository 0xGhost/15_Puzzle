// author: Yiang Lu
// Date created: 13/Oct/2019
#pragma once
#include "Board.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

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
	inline void operator+=(const ContinuousNumber& rhs)
	{
		column += rhs.column;
		row += rhs.row;
		columnReverse += rhs.columnReverse;
		rowReverse += rhs.rowReverse;
	}
};


class NCLBoard :
	public Board
{
public:
	NCLBoard(const int& size, const int& min, const int& max) throw (std::invalid_argument) :Board(size, min, max) {}
	NCLBoard(const int& size, int* input) throw (std::invalid_argument);
	NCLBoard(const NCLBoard& rhs);
	virtual ~NCLBoard() {};
	bool IsTurnEnd(); // check if this board is a turn end 
	ContinuousNumber CheckContinuous(); // check full continuous in all directions
	ContinuousNumber CheckContinuous(int length); // check partial continuous in all directions
	string ToString();
	vector<char> ToVector();

private:

};

