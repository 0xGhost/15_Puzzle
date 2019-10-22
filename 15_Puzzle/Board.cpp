// author: Yiang Lu
// Date created: 10/Oct/2019
#include "Board.h"
#include <deque>
#include <iomanip>
#include "Utility.h"

using std::deque;
using std::invalid_argument;



Board::Board(const int& size = 4, const int& min = 1, const int& max = 20)
	: SIZE(size), spaceX(size - 1), spaceY(size - 1), max(max)
{
	numberMaxLength = GetNumberLength(max);
	blocks = RandomGenerator(min, max);
}

Board::Board(const int& size, int* input)
	: SIZE(size), spaceX(size - 1), spaceY(size - 1), max(-1)
{
	blocks = new int[SIZE * SIZE];
	memcpy(blocks, input, SIZE * SIZE * sizeof(int));
	if (blocks[IndexOf(spaceX, spaceY)] != SPACE) // if SPACE is not in the bottom right
	{
		for (int i = 0; i < SIZE * SIZE; i++)
		{
			
			if (input[i] == SPACE) // set the SPACE block position
			{
				spaceX = i % SIZE;
				spaceY = i / SIZE;
			}
		}
	}
	// set the max length for print alignment
	for(int i = 0; i < SIZE * SIZE; i++)
		max = input[i] > max ? input[i] : max;
	numberMaxLength = GetNumberLength(max);
}

Board::Board(const Board& rhs)
	: SIZE(rhs.SIZE),
	spaceX(rhs.spaceX),
	spaceY(rhs.spaceY),
	max(rhs.max),
	numberMaxLength(rhs.numberMaxLength)
{
	this->blocks = new int[SIZE * SIZE]();
	memcpy(this->blocks, rhs.blocks, SIZE * SIZE * sizeof(int));
}

Board::~Board()
{
	delete[] blocks;
	blocks = nullptr;
}

bool Board::MoveCheck(const Direction& direction) const
{
	int a, b;
	return MoveCheck(direction, a, b);
}

bool Board::MoveCheck(const Direction& direction, int& positionX, int& positionY) const
{
	// get the SPACE block position after the move
	int positionX_Temp = ((direction & 1) ? spaceX + direction : spaceX);
	int positionY_Temp = ((direction & 1) ? spaceY : spaceY + (direction >> 1)); // '& 1' is '% 2' ;  '>> 1' is '/ 2'
	
	// check if the move is valid
	if (positionX_Temp < 0 || positionX_Temp >= SIZE || positionY_Temp < 0 || positionY_Temp >= SIZE)
		return false;
	
	positionX = positionX_Temp;
	positionY = positionY_Temp;
	return true;
}

void Board::MovePosition(const int& positionX, const int& positionY)
{
	blocks[IndexOf(spaceX, spaceY)] = blocks[IndexOf(positionX, positionY)];
	blocks[IndexOf(positionX, positionY)] = SPACE;
	spaceX = positionX;
	spaceY = positionY;
}

bool Board::Move(const Direction& direction)
{
	int positionX, positionY;

	if (!MoveCheck(direction, positionX, positionY))
		return false;

	MovePosition(positionX, positionY);
	return true;

}

bool Board::isEqualTo(const Comparable& rhs) const
{
	return memcmp(blocks, ((Board*)& rhs)->blocks, (long long)SIZE
		* SIZE * sizeof(int)) == 0;
}

int* Board::GetBlocks() const
{
	return blocks;
}

int* Board::RandomGenerator(const int& min, const int& max) const
{
	int size = SIZE * SIZE;
	int range = (max - min + 1);
	deque<int>* bucket = new deque<int>[range]; // a bucket that each slots is a deque
	int* array = new int[size];
	// loop through all numbers in range
	for (int number = min; number <= max; number++)
	{
		int b_index = rand() % range; // random find the bucket index for each number
		// random put the number in the front or back of a deque
		if (rand() & 1)
		{
			bucket[b_index].push_back(number);
		}
		else
		{
			bucket[b_index].push_front(number);
		}
	}
	// output the numbers in the bucket into array
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

int Board::IndexOf(const int& x, const int& y) const
{
	return y * SIZE + x;
}

std::ostream& Board::print(std::ostream& ostr, const Comparable& comparable) const
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			int block = ((Board*)& comparable)->blocks[IndexOf(j, i)];
			ostr << std::left << std::setw((long long)numberMaxLength + 2) << std::setfill(' '); // set space between numbers for alignment 
			
			if (block == SPACE)
				ostr << ' ';
			else
				ostr << block;
				
		}
		ostr << std::endl;
	}
	return ostr;
}
