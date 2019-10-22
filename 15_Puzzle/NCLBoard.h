// author: Yiang Lu
// Date created: 13/Oct/2019
#pragma once
#include "Board.h"
#include "BigPosInt.h"
#include <string>
#include <vector>
#include "ctpl_stl.h"

using std::string;
using std::vector;

struct ContinuousNumber
{
	unsigned long long column = 0;
	unsigned long long  row = 0;
	unsigned long long  columnReverse = 0;
	unsigned long long  rowReverse = 0;
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
	NCLBoard(const int& size, const int& min, const int& max) :Board(size, min, max) {}
	NCLBoard(const int& size, int* input) : Board(size, input){	}
	NCLBoard(const NCLBoard& rhs) : Board(rhs) {}
	virtual ~NCLBoard() {};
	bool IsTurnEnd(); // check if this board is a turn end 
	BigPosInt GetTotalContinuousNumber(const bool& containSpace, const int& partial) const; // return continuous number (all are the same)
	BigPosInt GetTotalContinuousNumber(const bool& containSpace) const; // return continuous number (all are the same)
	ContinuousNumber CheckContinuous(const bool& containSPACE) const; // check full continuous in all directions
	ContinuousNumber CheckContinuous(const bool& containSPACE, const int& length) const; // check partial continuous in all directions
	string ToString() const; // return a string represent the puzzle configuration
	vector<char> ToVector() const; // return a vector represent the puzzle configuration

private:
	 static ctpl::thread_pool thPool;
	// check if there are given length of continuous from given block position in given direction
	bool CheckContinuousFromPoint(const bool& containSPACE, const int& length, const int& x, const int& y, const Direction& direction) const;
};

