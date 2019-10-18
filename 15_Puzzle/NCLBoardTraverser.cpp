// Author: Yiang Lu
// Date created: 15/Oct/2019
#include "NCLBoardTraverser.h"
#include <functional>
#include <queue>
#include <iostream>

using std::queue;

NCLBoardTraverser::NCLBoardTraverser(NCLBoard* board, const bool& containSPACE) : size(0)
{
	Travers(board, containSPACE);
}

#define Queue
#ifdef Queue

ContinuousNumber NCLBoardTraverser::Travers(NCLBoard* board, const bool& containSPACE)
{
	size = board->SIZE;
	queue<NCLBoard*> queue;

	NCLBoard* newBoard = new NCLBoard(*board);
	queue.push(newBoard);

	boardSet.insert(newBoard->ToVector());
	NCLBoard *currentBoard;
	
	while (!queue.empty())
	{
		currentBoard = queue.front();
		queue.pop();
		vector<char> history = currentBoard->ToVector();
		
		int a = queue.size();

		if (currentBoard->IsTurnEnd())
		{
			totalContinuousNumber += currentBoard->CheckContinuous(containSPACE);
		}

		auto BoardMove = [&](Direction diretion)
		{
			if (currentBoard->MoveCheck(diretion))
			{
				NCLBoard* newBoard = new NCLBoard(*currentBoard);
				newBoard->Move(diretion);

				if (boardSet.count(newBoard->ToVector()) == 0)
				{
					queue.push(newBoard);
					boardSet.insert(newBoard->ToVector());
				}
				else
				{
					delete newBoard;
				}
			}
		};

		BoardMove(Direction::Top);
		BoardMove(Direction::Bottom);
		BoardMove(Direction::Left);
		BoardMove(Direction::Right);

		delete currentBoard;
		currentBoard = nullptr;
		
	}
	return totalContinuousNumber;
}
#endif
#ifdef Stack
ContinuousNumber NCLBoardTraverser::Travers(NCLBoard* board)
{
	size = board->SIZE;
	int count = 0;
	int Ccount = 0;
	int setcount = 0;
	vector<NCLBoard*> stack;
	NCLBoard* newBoard = new NCLBoard(*board);
	stack.push_back(newBoard);
	boardSet.insert(newBoard->ToVector());
	setcount++;
	NCLBoard* currentBoard;
	
	while (!stack.empty())
	{
		currentBoard = stack.back();
		stack.pop_back();
		vector<int> history = currentBoard->ToVector();
		
		if (currentBoard->IsTurnEnd())
		{
			count++;
			totalContinuousNumber += currentBoard->CheckContinuous();
		}
		if (currentBoard->MoveCheck(Direction::Top))
		{
			NCLBoard* newBoard = new NCLBoard(*currentBoard);
			newBoard->Move(Direction::Top);
			if (boardSet.count(newBoard->ToVector()) == 0)
			{
				stack.push_back(newBoard);
				boardSet.insert(newBoard->ToVector());
				setcount++;
			}
			else
			{
				delete newBoard;
			}
		}
		if (currentBoard->MoveCheck(Direction::Bottom))
		{
			NCLBoard* newBoard = new NCLBoard(*currentBoard);
			newBoard->Move(Direction::Bottom);
			if (boardSet.count(newBoard->ToVector()) == 0)
			{
				stack.push_back(newBoard);
				boardSet.insert(newBoard->ToVector());
				setcount++;
			}
			else
			{
				delete newBoard;
			}
		}
		if (currentBoard->MoveCheck(Direction::Left))
		{
			NCLBoard* newBoard = new NCLBoard(*currentBoard);
			newBoard->Move(Direction::Left);
			if (boardSet.count(newBoard->ToVector()) == 0)
			{
				stack.push_back(newBoard);
				boardSet.insert(newBoard->ToVector());
				setcount++;
			}
			else
			{
				delete newBoard;
			}
		}
		if (currentBoard->MoveCheck(Direction::Right))
		{
			NCLBoard* newBoard = new NCLBoard(*currentBoard);
			newBoard->Move(Direction::Right);
			if (boardSet.count(newBoard->ToVector()) == 0)
			{
				stack.push_back(newBoard);
				boardSet.insert(newBoard->ToVector());
				setcount++;
			}
			else
			{
				delete newBoard;
			}
		}
		delete currentBoard;
		currentBoard = nullptr;
	}
	return totalContinuousNumber;
}
#endif


