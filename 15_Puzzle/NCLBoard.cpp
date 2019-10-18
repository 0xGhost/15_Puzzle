// author: Yiang Lu
// Date created: 13/Oct/2019
#include "NCLBoard.h"

bool NCLBoard::IsTurnEnd()
{
	return (spaceX == (SIZE - 1) && spaceY == (SIZE - 1));
}

inline unsigned long Factorial(int number)
{
	unsigned long  factorial = 1;
	for (int i = 2; i <= number; ++i)
	{
		factorial *= i;
	}
	return factorial;
}

unsigned long NCLBoard::GetTotalContinuousNumber(const bool& containSpace, const int& partial) const
{
	unsigned long result = 0;
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
			result += (n - partial + 2) * Factorial(size - 2) / 2;
		}
		// not contain SPACE: 
			//possible continuous row configuration: n - partial + 1
			// reachable board configuration: (SIZE*SIZE - 4)! / 2 * 2
		result += (n - partial + 1) * Factorial(size - 3);
	}
	return result;
}

unsigned long NCLBoard::GetTotalContinuousNumber(const bool& containSpace) const
{
	return GetTotalContinuousNumber(containSpace, SIZE);
}

ContinuousNumber NCLBoard::CheckContinuous(const bool& containSPACE) const 
{
	/*brute force search*/
	ContinuousNumber result;

	for (int j = 0; j < SIZE; j++)
	{
		if (j == SIZE - 1 && !containSPACE)
		{
			break;
		}
		result.row++;
		for (int i = 0; i < SIZE - 1; i++)
		{
			if (blocks[IndexOf(i, j)] != blocks[IndexOf(i + 1, j)] - 1
				&& blocks[IndexOf(i, j)] != SPACE && blocks[IndexOf(i + 1, j)] != SPACE)
			{
				result.row--;
				break;
			}
		}
	}

	for (int j = 0; j < SIZE; j++)
	{
		if (j == SIZE - 1 && !containSPACE)
		{
			break;
		}
		result.rowReverse++;
		for (int i = 0; i < SIZE - 1; i++)
		{
			if (blocks[IndexOf(i, j)] != blocks[IndexOf(i + 1, j)] + 1
				&& blocks[IndexOf(i, j)] != SPACE && blocks[IndexOf(i + 1, j)] != SPACE)
			{
				result.rowReverse--;
				break;
			}
		}
	}

	for (int i = 0; i < SIZE; i++)
	{
		if (i == SIZE - 1 && !containSPACE)
		{
			break;
		}
		result.column++;
		for (int j = 0; j < SIZE - 1; j++)
		{
			if (blocks[IndexOf(i, j)] != blocks[IndexOf(i, j + 1)] - 1
				&& blocks[IndexOf(i, j)] != SPACE && blocks[IndexOf(i, j + 1)] != SPACE)
			{
				result.column--;
				break;
			}
		}
	}

	for (int i = 0; i < SIZE; i++)
	{
		if (i == SIZE - 1 && !containSPACE)
		{
			break;
		}
		result.columnReverse++;
		for (int j = 0; j < SIZE - 1; j++)
		{
			if (blocks[IndexOf(i, j)] != blocks[IndexOf(i, j + 1)] + 1
				&& blocks[IndexOf(i, j)] != SPACE && blocks[IndexOf(i, j + 1)] != SPACE)
			{
				result.columnReverse--;
				break;
			}
		}
	}

	return result;
}

ContinuousNumber NCLBoard::CheckContinuous(const bool& containSPACE, const int& length)
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

string NCLBoard::ToString()
{
	string str;
	for (int i = 0; i < SIZE * SIZE; i++)
	{
		str += std::to_string(blocks[i]);
		str += ' ';
	}
	return str;
}

vector<char> NCLBoard::ToVector()
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
	int moveX = (direction & 1) ? direction : 0;
	int moveY = (direction & 1) ? 0 : direction >> 1;
	int checkX = x;
	int checkY = y;
	int count = 1;

	while (count < length)
	{
		if (blocks[IndexOf(checkX, checkY)] == SPACE && !containSPACE)
			break;
		if (blocks[IndexOf(checkX, checkY)] + 1 == blocks[IndexOf(checkX + moveX, checkY + moveY)]
			|| blocks[IndexOf(checkX, checkY)] == SPACE 
			|| blocks[IndexOf(checkX + moveX, checkY + moveY)] == SPACE)
		{
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
