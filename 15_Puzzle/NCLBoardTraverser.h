#pragma once
#include "NCLBoard.h"
#include <set>
#include <unordered_map>
#include <unordered_set>

using std::set;
using std::string;
using std::unordered_map;
using std::unordered_set;
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

	ContinuousNumber Travers(NCLBoard *board);
	ContinuousNumber GetTotalContinuousNumber() { return totalContinuousNumber; }
private:
	Node* root = nullptr;
	int size;
	unordered_map<string, NCLBoard*> hashMap;
	unordered_set<string> boardSet;
	bool Search(const NCLBoard* board);
	ContinuousNumber totalContinuousNumber;
};

