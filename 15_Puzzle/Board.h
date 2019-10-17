// author: Yiang Lu
// Date created: 10/Oct/2019
#pragma once
#include "Comparable.h"
#include <stdexcept>

using std::invalid_argument;

enum Direction
{
	Top = -2,
	Left,
	Null,
	Right,
	Bottom
};

class Board : 
	public Comparable
{
public:
	const int SIZE; // size of the board

	Board(const int& size, const int& min, const int& max) throw (invalid_argument); // random generate a puzzle board
	Board(const int& size, int* input) throw (invalid_argument); // input a board using an array
	Board(const Board& board);
	virtual ~Board();
	bool MoveCheck(const Direction& direction) const;
	bool Move(const Direction& direction); // move the space to a direction
	bool isEqualTo(const Comparable& rhs) const override;
	int* GetBlocks() const;
	
protected:
	
	int* blocks; // blocks in the board
	int spaceX;// column position of space block (start from 0)
	int spaceY;// row position of space block (start from 0)
	int max; // the largest number in the board
	int IndexOf(const int& x, const int& y) const; // get 1D array index by 2D postion
	bool MoveCheck(const Direction& direction, int& positionX, int& positionY) const;
	void MovePosition(const int& positionX, const int& positionY);
	const int SPACE = -1; // The space block in the board is represent as -1


private:
	int numberMaxLength; // The max length of numbers that appear in the board. It is used for display the board
	int* RandomGenerator(const int& min, const int& max); // random generate non-repeating numbers in rang [min,max]. The space in the bottom right
	virtual std::ostream& print(std::ostream& ostr, const Comparable& comparable) const override;
};

