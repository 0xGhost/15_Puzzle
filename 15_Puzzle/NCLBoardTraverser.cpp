#include "NCLBoardTraverser.h"
#include <functional>

NCLBoardTraverser::NCLBoardTraverser()
{
}

void NCLBoardTraverser::Travers(NCLBoard* board)
{
	size = board->SIZE;
	std::function<void(Node**, NCLBoard*, Direction)> Insert = [=, &Insert](Node** tree, NCLBoard* board, Direction from)
	{
		if (*tree == nullptr)
		{
			if (boardSet.contains(board.toString())) return;
			*tree = new Node();
			(*tree)->board = board;
			(*tree)->from = from;
			// TODO: multi-threading
			if (from != Direction::Bottom && board->MoveCheck(Direction::Top))
			{
				NCLBoard *newBoard = board;
				newBoard->Move(Direction::Top);
				Insert(&(*tree)->top, newBoard, Direction::Top);
			}
			if (from != Direction::Top && board->MoveCheck(Direction::Bottom))
			{
				NCLBoard* newBoard = board;
				newBoard->Move(Direction::Bottom);
				Insert(&(*tree)->bottom, newBoard, Direction::Bottom);
			}
			if (from != Direction::Right && board->MoveCheck(Direction::Left))
			{
				NCLBoard* newBoard = board;
				newBoard->Move(Direction::Left);
				Insert(&(*tree)->left, newBoard, Direction::Left);
			}
			if (from != Direction::Left && board->MoveCheck(Direction::Right))
			{
				NCLBoard* newBoard = board;
				newBoard->Move(Direction::Right);
				Insert(&(*tree)->right, newBoard, Direction::Right);
			}
		}
	};
	Insert(&root, board, Direction::Null);
}

bool NCLBoardTraverser::Search(const NCLBoard* board)
{
	
}

