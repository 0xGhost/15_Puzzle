#include "NCLBoardTraverser.h"
#include <functional>
#include <queue>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::queue;

NCLBoardTraverser::NCLBoardTraverser(NCLBoard* board) : size(0)
{
	Travers(board);
}

// queue -> 1
// stack -> 0
#if 1

ContinuousNumber NCLBoardTraverser::Travers(NCLBoard* board)
{
	size = board->SIZE;
	int count = 0;
	int Ccount = 0;
	int setcount = 0;
	//vector<NCLBoard*> stack;
	queue<NCLBoard*> queue;
	//std::vector<vector<int>>::iterator it;//////////////////////vector history
	NCLBoard* newBoard = new NCLBoard(*board);
	queue.push(newBoard);
	//stack.push_back(newBoard);
	boardSet.insert(newBoard->ToVector()); setcount++;
	NCLBoard *currentBoard;
	
	while (!queue.empty())
	{
		//currentBoard = stack.back();
		currentBoard = queue.front();
		queue.pop();
		//stack.pop_back();
		vector<char> history = currentBoard->ToVector();
		//history.push_back(setcount);
		
		//boardHistory.push_back(currentBoard->ToVector());
		
		int a = queue.size();
		//cout << "Nturn" << *currentBoard << endl;
		if (currentBoard->IsTurnEnd())
		{
			count++;
			totalContinuousNumber += currentBoard->CheckContinuous();
			if (currentBoard->CheckContinuous().column > 0
				|| currentBoard->CheckContinuous().columnReverse > 0
				|| currentBoard->CheckContinuous().row > 0
				|| currentBoard->CheckContinuous().rowReverse > 0) Ccount++;
			//cout << "turn" << *currentBoard << endl;
			//cout << "setCount = " << setcount << endl;
			//cout << "a = " << stack.size() << endl;
		}
		if (currentBoard->MoveCheck(Direction::Top))
		{
			NCLBoard* newBoard = new NCLBoard(*currentBoard);
			newBoard->Move(Direction::Top);
			//it = std::find(boardHistory.begin(), boardHistory.end(), newBoard->ToVector());
			if //(it == boardHistory.end())
				(boardSet.count(newBoard->ToVector()) == 0)
			{
				queue.push(newBoard);
				boardSet.insert(newBoard->ToVector());
				setcount++;
				//stack.push_back(newBoard);
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
			//it = std::find(boardHistory.begin(), boardHistory.end(), newBoard->ToVector());
			if //(it == boardHistory.end())
				(boardSet.count(newBoard->ToVector()) == 0)
			{
				queue.push(newBoard);
				boardSet.insert(newBoard->ToVector());
				setcount++;
				//stack.push_back(newBoard);
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
			//it = std::find(boardHistory.begin(), boardHistory.end(), newBoard->ToVector());
			if //(it == boardHistory.end())
				(boardSet.count(newBoard->ToVector()) == 0)
			{
				queue.push(newBoard);
				boardSet.insert(newBoard->ToVector());
				setcount++;
				//stack.push_back(newBoard);
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
			//it = std::find(boardHistory.begin(), boardHistory.end(), newBoard->ToVector());
			if //(it == boardHistory.end())
			   (boardSet.count(newBoard->ToVector()) == 0)
			{
				queue.push(newBoard);
				boardSet.insert(newBoard->ToVector());
				setcount++;
				//stack.push_back(newBoard);
			}
			else
			{
				delete newBoard;
			}
		}
		//boardSet.erase(boardSet.find(history));
		delete currentBoard;
		currentBoard = nullptr;
		
	}
	
		

	cout << "turn count =" << count << endl;
	cout << "turn Ccount =" << Ccount << endl;
	cout << "setCount = " << setcount << endl;

	return totalContinuousNumber;
}

#else
ContinuousNumber NCLBoardTraverser::Travers(NCLBoard* board)
{
	size = board->SIZE;
	int count = 0;
	int Ccount = 0;
	int setcount = 0;
	vector<NCLBoard*> stack;
	//queue<NCLBoard*> queue;
	//std::vector<vector<int>>::iterator it;//////////////////////vector history
	NCLBoard* newBoard = new NCLBoard(*board);
	//queue.push(newBoard);
	stack.push_back(newBoard);
	boardSet.insert(newBoard->ToVector());
	setcount++;
	NCLBoard* currentBoard;
	
	while (!stack.empty())
	{
		currentBoard = stack.back();
		//currentBoard = queue.front();
		//queue.pop();
		stack.pop_back();
		vector<int> history = currentBoard->ToVector();
		//history.push_back(setcount);
		/*
		if (boardSet.count(history) != 0)
		{
			cout << "Noooo" << endl;
		}*/

		//boardHistory.push_back(currentBoard->ToVector());

		//cout << "Nturn" << *currentBoard << endl;
		if (currentBoard->IsTurnEnd())
		{
			count++;
			totalContinuousNumber += currentBoard->CheckContinuous();
			if (currentBoard->CheckContinuous().column > 0
				|| currentBoard->CheckContinuous().columnReverse > 0
				|| currentBoard->CheckContinuous().row > 0
				|| currentBoard->CheckContinuous().rowReverse > 0) Ccount++;
			//cout << "turn" << *currentBoard << endl;
			//cout << "setCount = " << setcount << endl;
			//cout << "a = " << stack.size() << endl;
		}
		if (currentBoard->MoveCheck(Direction::Top))
		{
			NCLBoard* newBoard = new NCLBoard(*currentBoard);
			newBoard->Move(Direction::Top);
			//it = std::find(boardHistory.begin(), boardHistory.end(), newBoard->ToVector());
			if //(it == boardHistory.end())
				(boardSet.count(newBoard->ToVector()) == 0)
			{
				//queue.push(newBoard);
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
			//it = std::find(boardHistory.begin(), boardHistory.end(), newBoard->ToVector());
			if //(it == boardHistory.end())
				(boardSet.count(newBoard->ToVector()) == 0)
			{
				//queue.push(newBoard);
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
			//it = std::find(boardHistory.begin(), boardHistory.end(), newBoard->ToVector());
			if //(it == boardHistory.end())
				(boardSet.count(newBoard->ToVector()) == 0)
			{
				//queue.push(newBoard);
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
			//it = std::find(boardHistory.begin(), boardHistory.end(), newBoard->ToVector());
			if //(it == boardHistory.end())
				(boardSet.count(newBoard->ToVector()) == 0)
			{
				//queue.push(newBoard);
				stack.push_back(newBoard);
				boardSet.insert(newBoard->ToVector());
				setcount++;
			}
			else
			{
				delete newBoard;
			}
		}
		//boardSet.erase(boardSet.find(history));
		delete currentBoard;
		currentBoard = nullptr;

	}
	cout << "turn count =" << count << endl;
	cout << "turn Ccount =" << Ccount << endl;
	cout << "setCount = " << setcount << endl;

	return totalContinuousNumber;
}
#endif


