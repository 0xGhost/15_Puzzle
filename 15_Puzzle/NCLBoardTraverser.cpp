#include "NCLBoardTraverser.h"
#include <functional>

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

NCLBoardTraverser::NCLBoardTraverser() : size(0)
{
	//boardSet = new unordered_set<vector<int>>();
}

NCLBoardTraverser::~NCLBoardTraverser()
{
	/*
	std::function<void(Node*)> TerminateTree = [&](Node* tree)
	{
		if (tree == nullptr)
		{
			std::cout << "tree is terminated" << std::endl;
			return;
		}

		if (tree->left != nullptr)
		{
			TerminateTree(tree->left);
		}
		if (tree->right != nullptr)
		{
			TerminateTree(tree->right);
		}
		if (tree->top != nullptr)
		{
			TerminateTree(tree->top);
		}
		if (tree->bottom != nullptr)
		{
			TerminateTree(tree->bottom);
		}

		delete tree->board;
		delete tree;
		tree = nullptr;
	};
	TerminateTree(root);
	*/
	//delete boardSet;

	_CrtDumpMemoryLeaks();
}

ContinuousNumber NCLBoardTraverser::Travers(NCLBoard* board)
{
	size = board->SIZE;
	int count = 0;
	vector<NCLBoard*> stack;

	NCLBoard* newBoard = new NCLBoard(*board);
	NCLBoard *currentBoard;
	stack.push_back(newBoard);
	while (!stack.empty())
	{
		currentBoard = stack.back();
		stack.pop_back();
		boardSet.insert(currentBoard->ToVector());
		if (currentBoard->IsTurnEnd())
		{
			count++;
			totalContinuousNumber += currentBoard->CheckContinuous();
			//cout << "turn" << *currentBoard << endl;
			
			cout << "a = " << stack.size() << endl;
		}
		if (currentBoard->MoveCheck(Direction::Top))
		{
			NCLBoard* newBoard = new NCLBoard(*currentBoard);
			newBoard->Move(Direction::Top);
			if (boardSet.count(newBoard->ToVector()) == 0)
				stack.push_back(newBoard);
		}
		if (currentBoard->MoveCheck(Direction::Bottom))
		{
			NCLBoard* newBoard = new NCLBoard(*currentBoard);
			newBoard->Move(Direction::Bottom);
			if (boardSet.count(newBoard->ToVector()) == 0)
				stack.push_back(newBoard);
		}
		if (currentBoard->MoveCheck(Direction::Left))
		{
			NCLBoard* newBoard = new NCLBoard(*currentBoard);
			newBoard->Move(Direction::Left);
			if (boardSet.count(newBoard->ToVector()) == 0)
				stack.push_back(newBoard);
		}
		if (currentBoard->MoveCheck(Direction::Right))
		{
			NCLBoard* newBoard = new NCLBoard(*currentBoard);
			newBoard->Move(Direction::Right);
			if (boardSet.count(newBoard->ToVector()) == 0)
				stack.push_back(newBoard);
		}
		
		delete currentBoard;
		currentBoard = nullptr;
		cout << "turn count =" << count << endl;
	}


	/*
	std::function<void(Node**, NCLBoard*, Direction)> Insert = [&](Node** tree, NCLBoard* board, Direction from)
	{
		count++;
		if (*tree == nullptr)
		{
			if (board->IsTurnEnd())
			{
				
				totalContinuousNumber += board->CheckContinuous();
				
			}cout << "R count = " << count << endl;//cout << *board; /////////////////////////////debug
			
			*tree = new Node();
			(*tree)->board = board;
			(*tree)->from = from;
			boardSet->insert(board->ToVector());

			// TODO: multi-threading
			if (from != Direction::Bottom && board->MoveCheck(Direction::Top))
			{
				NCLBoard* newBoard = new NCLBoard(*board);
				newBoard->Move(Direction::Top);
				if (boardSet->count(newBoard->ToVector()) == 0)
					Insert(&(*tree)->top, newBoard, Direction::Top);
			}
			if (from != Direction::Top && board->MoveCheck(Direction::Bottom))
			{
				NCLBoard* newBoard = new NCLBoard(*board);
				newBoard->Move(Direction::Bottom);
				if (boardSet->count(newBoard->ToVector()) == 0)
					Insert(&(*tree)->bottom, newBoard, Direction::Bottom);
			}
			if (from != Direction::Right && board->MoveCheck(Direction::Left))
			{
				NCLBoard* newBoard = new NCLBoard(*board);
				newBoard->Move(Direction::Left);
				if (boardSet->count(newBoard->ToVector()) == 0)
					Insert(&(*tree)->left, newBoard, Direction::Left);
			}
			if (from != Direction::Left && board->MoveCheck(Direction::Right))
			{
				NCLBoard* newBoard = new NCLBoard(*board);
				newBoard->Move(Direction::Right);
				if (boardSet->count(newBoard->ToVector()) == 0)
					Insert(&(*tree)->right, newBoard, Direction::Right);
			}
			
		}
		count--;
	};
	//NCLBoard *newBoard = new NCLBoard(*board);
	//Insert(&root, newBoard, Direction::Null);
	*/
	return totalContinuousNumber;
}

bool NCLBoardTraverser::Search(const NCLBoard* board)
{
	return true;
}

