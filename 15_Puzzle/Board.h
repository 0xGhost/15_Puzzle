// author: Yiang Lu
// Date created: 10/Oct/2019
#pragma once
#include "Comparable.h"

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
	const int SIZE; // size of the board eg: SIZE = 4 means 15-puzzle

	Board(const int& size, const int& min, const int& max); // random generate a puzzle board, make sure argument is vaild
	Board(const int& size, int* input); // input a board using an array, make sure the input array is in correct format
	Board(const Board& board); // copy constructor
	virtual ~Board();
	bool MoveCheck(const Direction& direction) const; // check if a move is possible
	bool Move(const Direction& direction); // move the space to a direction
	bool isEqualTo(const Comparable& rhs) const override;
	int* GetBlocks() const; // return the array stored blocks
	
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
	int* RandomGenerator(const int& min, const int& max) const; // random generate non-repeating numbers in rang [min,max]. The space in the bottom right
	virtual std::ostream& print(std::ostream& ostr, const Comparable& comparable) const override;
};

