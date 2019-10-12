#pragma once
#include "Comparable.h"

enum Direction
{
	Top = -2,
	Left,
	Right = 1,
	Bottom
};

class Board : public Comparable
{
public:

	Board(const int& size, const int& min, const int& max); // random generate a puzzle board
	Board(const int& size, int* input); // input a board using an array
	virtual ~Board();
	//virtual const int** GetBoard();
	virtual void Move(const Direction&); // move the space to a direction
	virtual bool isEqualTo(const Comparable& rhs) override;

private:
	const int SIZE; // size of the board
	const int SPACE = -1;
	int* blocks; // blocks in the board
	// position of space block (start from 0)
	int spaceX;
	int spaceY;
	int numberMaxLength;
	
	int* RandomGenerator(const int& min, const int& max); // random generate non-repeating numbers in rang [min,max]. The space in the bottom right
	int IndexOf(const int& x, const int& y); // get 1D array index by 2D postion
	virtual std::ostream& print(std::ostream& ostr, const Comparable& comparable);
};

