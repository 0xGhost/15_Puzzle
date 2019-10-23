// Author: Yiang Lu
// Date created: 15/Oct/2019
#include "NCLBoardTraverser.h"
#include <functional>
#include <queue>
#include <iostream>


using std::queue;

 ctpl::thread_pool NCLBoardTraverser::thPool(4);

NCLBoardTraverser::NCLBoardTraverser(NCLBoard* board, const bool& containSPACE) : size(0)
{
	Travers(board, containSPACE);
}

#define Queue
#ifdef Queue

// BFS to travers all possible configurations and check the continuous if it is a "turn end"
ContinuousNumber NCLBoardTraverser::Travers(NCLBoard* board, const bool& containSPACE)
{
	size = board->SIZE;
	queue<NCLBoard*> queue; // pending queue stored the Boards that pending to be processed
	// initialize
	NCLBoard* newBoard = new NCLBoard(*board);
	queue.push(newBoard);
	boardSet.insert(newBoard->ToVector());
	NCLBoard *currentBoard;
	
	while (!queue.empty())
	{
		currentBoard = queue.front(); // get one Board in queue from pending state to processing state
		queue.pop();

		if (currentBoard->IsTurnEnd()) // check if this configuration is a "turn end"
		{
			totalContinuousNumber += currentBoard->CheckContinuous(containSPACE);
		}

		auto BoardMove = [&](int, Direction diretion)
		{
			if (currentBoard->MoveCheck(diretion)) // check if a move is possible
			{
				NCLBoard* newBoard = new NCLBoard(*currentBoard);
				newBoard->Move(diretion);
				std::shared_lock<std::shared_mutex> lock1(historyMutex);
				if (boardSet.count(newBoard->ToVector()) == 0) // check if this configuration is already searched
				{
					lock1.unlock();
					std::unique_lock<std::shared_mutex> lock2(historyMutex);
					queue.push(newBoard); // add this board into the end of pending queue
					boardSet.insert(newBoard->ToVector()); // add this board into the searching history
				}
				else
				{
					delete newBoard;
				}
			}
		};
#if 0
		
		auto tFuture = thPool.push(BoardMove, Direction::Top);
		auto bFuture = thPool.push(BoardMove, Direction::Bottom);
		auto lFuture = thPool.push(BoardMove, Direction::Left);
		auto rFuture = thPool.push(BoardMove, Direction::Right);

		tFuture.get();
		bFuture.get();
		lFuture.get();
		rFuture.get();
		
#else
		BoardMove(1, Direction::Top);
		BoardMove(1, Direction::Bottom);
		BoardMove(1, Direction::Left);
		BoardMove(1, Direction::Right);
#endif
		delete currentBoard;
		currentBoard = nullptr;
		
	}
	return totalContinuousNumber;
}
#endif
#ifdef Stack
// BFS to travers all possible configurations and check the continuous if it is a "turn end" 
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


