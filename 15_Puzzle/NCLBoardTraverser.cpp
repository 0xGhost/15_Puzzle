#include "NCLBoardTraverser.h"
#include <functional>

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

NCLBoardTraverser::NCLBoardTraverser() : size(0)
{
}

NCLBoardTraverser::~NCLBoardTraverser()
{
	std::function<void(Node*)> TerminateTree = [&TerminateTree](Node* tree)
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
	_CrtDumpMemoryLeaks();
}

ContinuousNumber NCLBoardTraverser::Travers(NCLBoard* board)
{
	size = board->SIZE;
	std::function<void(Node**, NCLBoard*, Direction)> Insert = [=, &Insert](Node** tree, NCLBoard* board, Direction from)
	{
		if (*tree == nullptr)
		{
			// This board configuration not appear before
			/*
			if (boardSet.count(board->ToString()) != 0)
			{

				return;
			}
			*/
			if (board->IsTurnEnd())
			{
				totalContinuousNumber += board->CheckContinuous();
				cout << *board << endl; /////////////////////////////debug
			}
			
			*tree = new Node();
			(*tree)->board = board;
			(*tree)->from = from;
			boardSet.insert(board->ToString());

			// TODO: multi-threading
			if (from != Direction::Bottom && board->MoveCheck(Direction::Top))
			{
				NCLBoard* newBoard = new NCLBoard(*board);
				newBoard->Move(Direction::Top);
				if (boardSet.count(newBoard->ToString()) == 0)
					Insert(&(*tree)->top, newBoard, Direction::Top);
			}
			if (from != Direction::Top && board->MoveCheck(Direction::Bottom))
			{
				NCLBoard* newBoard = new NCLBoard(*board);
				newBoard->Move(Direction::Bottom);
				if (boardSet.count(newBoard->ToString()) == 0)
					Insert(&(*tree)->bottom, newBoard, Direction::Bottom);
			}
			if (from != Direction::Right && board->MoveCheck(Direction::Left))
			{
				NCLBoard* newBoard = new NCLBoard(*board);
				newBoard->Move(Direction::Left);
				if (boardSet.count(newBoard->ToString()) == 0)
					Insert(&(*tree)->left, newBoard, Direction::Left);
			}
			if (from != Direction::Left && board->MoveCheck(Direction::Right))
			{
				NCLBoard* newBoard = new NCLBoard(*board);
				newBoard->Move(Direction::Right);
				if (boardSet.count(newBoard->ToString()) == 0)
					Insert(&(*tree)->right, newBoard, Direction::Right);
			}
			
		}
	};
	NCLBoard *newBoard = new NCLBoard(*board);
	Insert(&root, newBoard, Direction::Null);
	return totalContinuousNumber;
}

bool NCLBoardTraverser::Search(const NCLBoard* board)
{
	return true;
}

