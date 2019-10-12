#include "Board.h"
#include <iomanip>

inline int GetNumberLength(int number)
{
	int length = 0;
	while (number)
	{
		number /= 10;
		length++;
	}
	return length;
}

Board::Board(int size, int min, int max) : SIZE(size), spaceX(size), spaceY(size)
{
	numberMaxLength = GetNumberLength(max);
	blocks = RandomGenerator(min, max);
}

Board::Board(int size, int* input) : SIZE(size), spaceX(size), spaceY(size)
{
	blocks = (int**)input;
	int max = -1;
	for (int i = 0; i < SIZE * SIZE; i++)
	{
		max = input[i] > max ? input[i] : max;
	}
	numberMaxLength = GetNumberLength(max);
}

Board::~Board()
{
	for (int i = 0; i < SIZE; i++)
	{
		delete[] blocks;
	}
	delete[] blocks;
	blocks = nullptr;
}

const int** Board::GetBoard()
{
	return blocks;
}

void Board::Move(const Direction& direction)
{
	int postionX = (direction & 1) ? spaceX + direction : spaceX;
	int postionY = (direction & 1) ? spaceY : spaceY + (direction >> 1);
	blocks[spaceX][spaceY] = blocks[postionX][postionY];
	blocks[postionX][postionY] = SPACE;
}

bool Board::isEqualTo(const Comparable& rhs)
{
	return memcmp(blocks, ((Board*)&rhs)->GetBoard(), SIZE 
	* SIZE * sizeof(int)) == 0;
}

std::ostream& Board::print(std::ostream& ostr, const Comparable& comparable)
{
	ostr << std::endl;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			ostr << std::setw(numberMaxLength + 1) << (i==j==SIZE ? ' ' : ((Board*)&comparable)->blocks[i][j]);
		}
		ostr << std::endl;
	}
	ostr << std::endl;
	return ostr;
}
