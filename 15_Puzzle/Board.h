// author: Yiang Lu
// Date created: 10/Oct/2019
#pragma once
#include "Comparable.h"

enum Direction
{
	Top = -2,
	Left,
	Right = 1,
	Bottom
};

class Board : 
	public Comparable
{
public:

	Board(const int& size, const int& min, const int& max); // random generate a puzzle board
	Board(const int& size, int* input); // input a board using an array
	virtual ~Board();
	virtual bool Move(const Direction&); // move the space to a direction
	bool isEqualTo(const Comparable& rhs) override; 

protected:
	const int SIZE; // size of the board
	int* blocks; // blocks in the board
	int spaceX;// column position of space block (start from 0)
	int spaceY;// row position of space block (start from 0)
	int max; // the largest number in the board
	int IndexOf(const int& x, const int& y); // get 1D array index by 2D postion

private:
	int numberMaxLength; // The max length of numbers that appear in the board. It is used for display the board
	const int SPACE = -1; // The space block in the board is represent as -1
	int* RandomGenerator(const int& min, const int& max); // random generate non-repeating numbers in rang [min,max]. The space in the bottom right
	virtual std::ostream& print(std::ostream& ostr, const Comparable& comparable);
};

