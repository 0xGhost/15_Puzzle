// author: Yiang Lu
// Date created: 13/Oct/2019
#include "NCLBoard.h"
#include <stdexcept>

using std::invalid_argument;

NCLBoard::NCLBoard(const int& size, int* input) throw (invalid_argument) : Board(size, input)
{
	bool* bucket = new bool[max + 1];
	memset(bucket, false, (max + 1) * sizeof(bool));
	for (int i = 0; i < SIZE * SIZE; i++)
	{
		if (input[i] == -1) continue;
		else
		{
			if (bucket[input[i]])
				throw invalid_argument("duplicate number detected: " + input[i]);
			else
				bucket[input[i]] = true;
		}
	}
	// TODO: throw exception if same number appear in the input array
	delete[] bucket;
	bucket = nullptr;
}

NCLBoard::NCLBoard(const NCLBoard& rhs) : Board(rhs)
{
}


bool NCLBoard::IsTurnEnd()
{
	return (spaceX == (SIZE - 1) && spaceY == (SIZE - 1));
}

ContinuousNumber NCLBoard::CheckContinuous()
{
	// TODO: "water fall" algorithm
	// idea: a board can not contain both continuous row and continuous column
	/*brute force search*/
	ContinuousNumber result;// = new ContinuousNumber();

	for (int j = 0; j < SIZE; j++)
	{
		result.row++;
		for (int i = 0; i < SIZE - 1; i++)
		{
			if (blocks[IndexOf(i, j)] != blocks[IndexOf(i + 1, j)] - 1
				&& blocks[IndexOf(i, j)] != -1 && blocks[IndexOf(i + 1, j)] != -1)
			{
				result.row--;
				break;
			}
		}
	}

	for (int j = 0; j < SIZE; j++)
	{
		result.rowReverse++;
		for (int i = 0; i < SIZE - 1; i++)
		{
			if (blocks[IndexOf(i, j)] != blocks[IndexOf(i + 1, j)] + 1
				&& blocks[IndexOf(i, j)] != -1 && blocks[IndexOf(i + 1, j)] != -1)
			{
				result.rowReverse--;
				break;
			}
		}
	}

	for (int i = 0; i < SIZE; i++)
	{
		result.column++;
		for (int j = 0; j < SIZE - 1; j++)
		{
			if (blocks[IndexOf(i, j)] != blocks[IndexOf(i, j + 1)] - 1
				&& blocks[IndexOf(i, j)] != -1 && blocks[IndexOf(i, j + 1)] != -1)
			{
				result.column--;
				break;
			}
		}
	}

	for (int i = 0; i < SIZE; i++)
	{
		result.columnReverse++;
		for (int j = 0; j < SIZE - 1; j++)
		{
			if (blocks[IndexOf(i, j)] != blocks[IndexOf(i, j + 1)] + 1
				&& blocks[IndexOf(i, j)] != -1 && blocks[IndexOf(i, j + 1)] != -1)
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
