#pragma once
#include "NCLBoard.h"
#include <set>

using std::set;
using std::string;

struct Node
{
	NCLBoard* board = nullptr;
	Node* top = nullptr;
	Node* bottom = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
	Direction from = Null;
};

class NCLBoardTraverser
{
public:
	NCLBoardTraverser();
	~NCLBoardTraverser();

	void Travers(NCLBoard *board);
	 
private:
	Node* root = nullptr;
	int size;
	set<string> boardSet;
	bool Search(const NCLBoard* board);

};

