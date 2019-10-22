// author: Yiang Lu
// Date created: 13/Oct/2019
#include "NCLBoard.h"
#include "Utility.h"
#include "BigPosInt.h"

// calculate: start * (start + 1) * .... * (end - 1) * end
inline BigPosInt Factorial(size_t start, size_t end) 
{
	BigPosInt factorial = 1;
	for (size_t i = start; i <= end; ++i)
	{
		factorial *= i;
	}
	return factorial;
}

bool NCLBoard::IsTurnEnd()
{
	return (spaceX == (SIZE - 1) && spaceY == (SIZE - 1));
}

BigPosInt NCLBoard::GetTotalContinuousNumber(const bool& containSpace, const int& partial) const
{
	BigPosInt result = 0;
	// sort (pre process)
	int size = SIZE * SIZE - 1;
	int* blocks = new int[size];
	memcpy(blocks, this->blocks, size * sizeof(int));
	std::qsort(blocks, size, sizeof(int), [](const void* a, const void* b) -> int {return *(int*)a - *(int*)b; });
	
	// find all continuous parts in array blocks 
	vector<int> lengthOfCP;
	int count = 0;
	for (int i = 0; i < size - 1; i++)
	{
		if (blocks[i] + 1 == blocks[i + 1])
		{
			count++;
		}
		else
		{
			if (count > 0)
			{
				lengthOfCP.push_back(count + 1);
			}
			count = 0;
		}
	}
	if (count > 0)
	{
		lengthOfCP.push_back(count + 1);
	}

	delete[] blocks;
	blocks = nullptr;
	// for each continuous parts(n: length of each part)
	for (const int& n : lengthOfCP)
	{
		// contain SPACE: 
		if (containSpace)
		{
			// possible continuous row configuration: n - (partial - 1) + 1
			// reachable board configuration: (SIZE*SIZE - 3)! / 2
			if ((n - partial + 2) > 0)
				result +=  Factorial(3, size - 2) * (n - partial + 2);
		}
		// not contain SPACE: 
			//possible continuous row configuration: n - partial + 1
			// reachable board configuration: (SIZE*SIZE - 4)! / 2 * (SIZE - 1)
		if ((n - partial + 1) > 0)
			result +=  Factorial(3, size - 3) * (n - partial + 1) * (SIZE - 1);
	}
	return result;
}

BigPosInt NCLBoard::GetTotalContinuousNumber(const bool& containSpace) const
{
	return GetTotalContinuousNumber(containSpace, SIZE);
}

ContinuousNumber NCLBoard::CheckContinuous(const bool& containSPACE) const 
{
	return CheckContinuous(containSPACE, SIZE);
}

ContinuousNumber NCLBoard::CheckContinuous(const bool& containSPACE, const int& length) const
{
	ContinuousNumber result;

	for (int j = 0; j < SIZE; j++)
	{
		for (int i = 0; i <= SIZE - length; i++)
		{
			result.row += CheckContinuousFromPoint(containSPACE, length, i, j, Direction::Right);
			result.column += CheckContinuousFromPoint(containSPACE, length, j, i, Direction::Bottom);
		}
	}

	for (int j = 0; j < SIZE; j++)
	{
		for (int i = SIZE - 1; i >= length - 1; i--)
		{
			result.rowReverse += CheckContinuousFromPoint(containSPACE, length, i, j, Direction::Left);
			result.columnReverse += CheckContinuousFromPoint(containSPACE, length, j, i, Direction::Top);
		}
	}

	return result;
}

string NCLBoard::ToString() const
{
	string str;
	for (int i = 0; i < SIZE * SIZE; i++)
	{
		str += std::to_string(blocks[i]);
		str += ' ';
	}
	return str;
}

vector<char> NCLBoard::ToVector() const
{
	vector<char> vec;
	for (int i = 0; i < SIZE * SIZE; i++)
	{
		if(blocks[i] == -1)
			vec.push_back('0');
		vec.push_back(blocks[i] + '0');
	}
	return vec;
}

bool NCLBoard::CheckContinuousFromPoint(const bool& containSPACE, const int& length, const int& x, const int& y, const Direction& direction) const
{
	int result;
	// the next block position offset according to current block
	int moveX = (direction & 1) ? direction : 0;
	int moveY = (direction & 1) ? 0 : direction >> 1;
	// the current block position
	int checkX = x;
	int checkY = y;
	int count = 1;

	while (count < length)
	{
		// check if cannot contain SPACE block
		if ((blocks[IndexOf(checkX, checkY)] == SPACE || blocks[IndexOf(checkX + moveX, checkY + moveY)] == SPACE) && !containSPACE)
			return false;

		if (blocks[IndexOf(checkX, checkY)] + 1 == blocks[IndexOf(checkX + moveX, checkY + moveY)]
			|| blocks[IndexOf(checkX, checkY)] == SPACE 
			|| blocks[IndexOf(checkX + moveX, checkY + moveY)] == SPACE)
		{
			// move current block position to next block position using the offset
			checkX += moveX;
			checkY += moveY;
			count++;
		}
		else
		{
			return false;
		}
	} 
	return true;
}
