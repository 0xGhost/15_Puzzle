// author: Yiang Lu
// Date created: 13/Oct/2019
#include "NCLBoard.h"

bool NCLBoard::IsTurnEnd()
{
	return spaceX == spaceY == (SIZE - 1) ? true : false;
}

ContinuousNumber* NCLBoard::CheckContinuous()
{
	// TODO: "water fall" algorithm
	// idea: a board can not contain both continuous row and continuous column
	/*brute force search*/
	ContinuousNumber *result = new ContinuousNumber();

	for (int j = 0; j < SIZE; j++)
	{
		result->row++;
		for (int i = 0; i < SIZE - 1; i++)
		{
			if (blocks[IndexOf(i, j)] != blocks[IndexOf(i + 1, j)] - 1
				&& blocks[IndexOf(i, j)] != -1 && blocks[IndexOf(i + 1, j)] != -1)
			{
				result->row--;
				break;
			}
		}
	}

	for (int j = 0; j < SIZE; j++)
	{
		result->rowReverse++;
		for (int i = 0; i < SIZE - 1; i++)
		{
			if (blocks[IndexOf(i, j)] != blocks[IndexOf(i + 1, j)] + 1
				&& blocks[IndexOf(i, j)] != -1 && blocks[IndexOf(i + 1, j)] != -1)
			{
				result->rowReverse--;
				break;
			}
		}
	}

	for (int i = 0; i < SIZE; i++)
	{
		result->column++;
		for (int j = 0; j < SIZE - 1; j++)
		{
			if (blocks[IndexOf(i, j)] != blocks[IndexOf(i, j + 1)] - 1
				&& blocks[IndexOf(i, j)] != -1 && blocks[IndexOf(i, j + 1)] != -1)
			{
				result->column--;
				break;
			}
		}
	}

	for (int i = 0; i < SIZE; i++)
	{
		result->columnReverse++;
		for (int j = 0; j < SIZE - 1; j++)
		{
			if (blocks[IndexOf(i, j)] != blocks[IndexOf(i, j + 1)] + 1
				&& blocks[IndexOf(i, j)] != -1 && blocks[IndexOf(i, j + 1)] != -1)
			{
				result->columnReverse--;
				break;
			}
		}
	}

	return result;
}
