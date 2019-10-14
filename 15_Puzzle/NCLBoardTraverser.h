#pragma once
#include "NCLBoard.h"

class NCLBoardTraverser
{
public:
	NCLBoardTraverser();
	~NCLBoardTraverser();

	void Search(const NCLBoard board);

private:
	NCLBoard* root;
};

