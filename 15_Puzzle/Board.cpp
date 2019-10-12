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

Board::Board(const int& size = 4, const int& min = 1, const int& max = 20) : SIZE(size), spaceX(size), spaceY(size)
{
	numberMaxLength = GetNumberLength(max);
	blocks = RandomGenerator(min, max);
}

Board::Board(const int& size, int* input) : SIZE(size), spaceX(size), spaceY(size)
{
	blocks = new int[SIZE * SIZE];
	memcpy(blocks, input, SIZE * SIZE * sizeof(int));

	int max = -1;
	for (int i = 0; i < SIZE * SIZE; i++)
	{
		max = input[i] > max ? input[i] : max;
		if (input[i] == -1)
		{
			spaceX = i % SIZE;
			spaceY = i / SIZE;
		}
	}
	numberMaxLength = GetNumberLength(max);
}

Board::~Board()
{
	delete[] blocks;
	blocks = nullptr;
}

void Board::Move(const Direction& direction)
{

	int postionX = ((direction & 1) ? spaceX + direction : spaceX);
	int postionY = ((direction & 1) ? spaceY : spaceY + (direction >> 1));
	blocks[IndexOf(spaceX, spaceY)] = blocks[IndexOf(postionX,postionY)];
	blocks[IndexOf(postionX, postionY)] = SPACE;
}

bool Board::isEqualTo(const Comparable& rhs)
{
	return memcmp(blocks, ((Board*)&rhs)->blocks, (long long)SIZE 
	* SIZE * sizeof(int)) == 0;
}

int* Board::RandomGenerator(const int& min, const int& max)
{
	int* a = new int[SIZE];
	return a;
}

int Board::IndexOf(const int& x, const int& y)
{
	return y * SIZE + x;
}

std::ostream& Board::print(std::ostream& ostr, const Comparable& comparable)
{
	ostr << std::endl;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			ostr << std::setw((long long)numberMaxLength + 1) << (i == j == SIZE ? ' ' : ((Board*)& comparable)->blocks[IndexOf(i, j)]);
		}
		ostr << std::endl;
	}
	ostr << std::endl;
	return ostr;
}
