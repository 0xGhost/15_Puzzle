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

unsigned long NCLBoard::GetTotalContinuousNumber(bool containSpace) const
{
	unsigned long result = 0;
	// sort (pre process)
	int size = SIZE * SIZE - 1;
	int* blocks = new int[size];
	memcpy(blocks, this->blocks, size * sizeof(int));
	for (int i = 1; i < size; i++)
	{
		for (int j = size - 1; j >= i; j--)
		{
			if (blocks[j] < blocks[j - 1])
			{
				int temp = blocks[j];
				blocks[j] = blocks[j - 1];
				blocks[j - 1] = temp;
			}
			
		}
	}
	
	// find all continuous parts in array blocks 
	vector<int> lengthOfCP;
	int count = 0;
	for (int i = 0; i < size; i++)
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
	// for each continuous parts(n: length of each part)
	for (const int& n : lengthOfCP)
	{
		// contain SPACE: 
		if (containSpace)
		{
			// possible continuous row configuration: n - (SIZE - 1) + 1
			// reachable board configuration: (SIZE*SIZE - 3)! / 2
			result += (n - SIZE + 2) * Factorial(size - 2) / 2;
		}
		// not contain SPACE: 
			//possible continuous row configuration: n - SIZE + 1
			// reachable board configuration: (SIZE*SIZE - 4)! / 2 * 2
		result += (n - SIZE + 1) * Factorial(size - 3);
	}
	return result;
}

ContinuousNumber NCLBoard::CheckContinuous(bool containSPACE)
{
	// TODO: "water fall" algorithm
	// idea: a board can not contain both continuous row and continuous column
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

vector<int> NCLBoard::ToVector()
{
	vector<int> vec;
	for (int i = 0; i < SIZE * SIZE; i++)
	{
		vec.push_back(blocks[i]);
	}
	return vec;
}
