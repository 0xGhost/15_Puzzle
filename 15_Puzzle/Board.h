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

	Board(int size = 4, int min = 1, int max = 20); // random generate a puzzle board
	Board(int size, int* input); // input a board using an array
	virtual ~Board();
	virtual const int** GetBoard();
	virtual void Move(const Direction&); // move the space to a direction
	virtual bool isEqualTo(const Comparable& rhs) override;

private:
	const int SIZE; // size of the board
	const int SPACE = -1;
	int** blocks; // blocks in the board
	// position of space block (start from 0)
	int spaceX;
	int spaceY;
	int numberMaxLength;
	
	int** RandomGenerator(int min, int max); 
	virtual std::ostream& print(std::ostream& ostr, const Comparable& comparable);
};

