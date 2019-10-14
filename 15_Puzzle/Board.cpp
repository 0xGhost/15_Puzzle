// author: Yiang Lu
// Date created: 10/Oct/2019
#include "Board.h"
#include <deque>

#include <iomanip>

using std::deque;
using std::invalid_argument;

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

Board::Board(const int& size = 4, const int& min = 1, const int& max = 20) throw (invalid_argument) 
	: SIZE(size), spaceX(size), spaceY(size), max(max)
{
	if ((max - min + 1) < (size * size - 1))
		throw invalid_argument("random range is smaller than numbers of blocks");
	if(min <= 0)
		throw invalid_argument("argument min must be positive integer");
	numberMaxLength = GetNumberLength(max);
	blocks = RandomGenerator(min, max);
}

Board::Board(const int& size, int* input) throw (invalid_argument) 
	: SIZE(size), spaceX(size), spaceY(size), max(-1)
{
	blocks = new int[SIZE * SIZE];
	memcpy(blocks, input, SIZE * SIZE * sizeof(int));
	bool spaceFlag = false;
	for (int i = 0; i < SIZE * SIZE; i++)
	{
		max = input[i] > max ? input[i] : max;
		if(input[i] <= 0 && input[i] != -1)
			throw invalid_argument("value of non-space blocks must be positive integer");
		if (input[i] == -1)
		{
			if (!spaceFlag)
				spaceFlag = true;
			else
				throw invalid_argument("more than one space block");
			spaceX = i % SIZE;
			spaceY = i / SIZE;
		}
	}
	numberMaxLength = GetNumberLength(max);
}

Board::Board(const Board* rhs) 
	: SIZE(rhs->SIZE), 
	spaceX(rhs->spaceX),
	spaceY(rhs->spaceY),
	max(rhs->max),
	numberMaxLength(rhs->numberMaxLength)
{
	memcpy(this->blocks, rhs->blocks, SIZE * SIZE * sizeof(int));
}

Board::~Board()
{
	delete[] blocks;
	blocks = nullptr;
}

bool Board::MoveCheck(const Direction& direction)
{
	int a, b;
	return MoveCheck(direction, a, b);
}

bool Board::MoveCheck(const Direction& direction, int& positionX, int& positionY)
{
	// get the space position after the move
	positionX = ((direction & 1) ? spaceX + direction : spaceX);
	positionY = ((direction & 1) ? spaceY : spaceY + (direction >> 1));
	// check if the move is valid
	if (positionX < 0 || positionX >= SIZE || positionY < 0 || positionY >= SIZE)
		return false;
	/*
	//TODO: check if the code above is quicker then behand
	int postionX1 = ((direction % 2) ? spaceX + direction : spaceX);
	int postionY1 = ((direction % 2) ? spaceY : spaceY + (direction / 2));
	*/
	return true;
}

void Board::MovePosition(const int& positionX, const int& positionY)
{
	blocks[IndexOf(spaceX, spaceY)] = blocks[IndexOf(positionX, positionY)];
	blocks[IndexOf(positionX, positionY)] = SPACE;
}

bool Board::Move(const Direction& direction)
{
	int positionX, positionY;

	if (!MoveCheck(direction, positionX, positionY))
		return false;
	
	MovePosition(positionX, positionY);
	return true;
	
}

bool Board::isEqualTo(const Comparable& rhs)
{
	return memcmp(blocks, ((Board*)&rhs)->blocks, (long long)SIZE 
	* SIZE * sizeof(int)) == 0;
}

int* Board::GetBlocks()
{
	return blocks;
}

int* Board::RandomGenerator(const int& min, const int& max)
{
	int size = SIZE * SIZE;
	int range = (max - min + 1);
	deque<int>* bucket = new deque<int>[range];
	int* array = new int[size];


	for (int number = min; number <= max; number++)
	{
		int b_index = rand() % range;
		if (rand() & 1)
		{
			bucket[b_index].push_back(number);
		}
		else
		{
			bucket[b_index].push_front(number);
		}
	}
	int index = 0;
	for (int i = 0; i < range; i++)
	{
		for (const int& number : bucket[i])
		{
			array[index++] = number;
			if (index >= size)
			{
				delete[] bucket;
				bucket = nullptr;
				array[size - 1] = -1;
				return array;
			}
		}
	}
	// defensive code
	delete[] bucket;
	bucket = nullptr;
	array[size - 1] = -1;
	return array;
	
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
			ostr << std::setw((long long)numberMaxLength + 1) << (i == j == SIZE ? ' ' : ((Board*)& comparable)->blocks[IndexOf(j, i)]);
		}
		ostr << std::endl;
	}
	ostr << std::endl;
	return ostr;
}
