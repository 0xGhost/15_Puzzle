// Author: Yiang Lu
// Date created: 15/Oct/2019
#pragma once
#include "NCLBoard.h"
#include <unordered_set>


using std::string;

using std::unordered_set;

namespace std {
	template <>
	struct hash<std::vector<char>> {
		size_t operator()(const vector<char>& v) const {
			std::hash<int> hasher;
			size_t seed = 0;
			for (int i : v) {
				seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			}
			return seed;
		}
	};
}

using MySet = std::unordered_set<std::vector<int>>;

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
	NCLBoardTraverser(NCLBoard* board, const bool& containSPACE);
	
	ContinuousNumber GetTotalContinuousNumber() { return totalContinuousNumber; }
private:
	//Node* root = nullptr;
	int size;
	unordered_set<vector<char>> boardSet;
	//vector<vector<int>> boardHistory;
	//bool Search(const NCLBoard* board);
	ContinuousNumber totalContinuousNumber;
	ContinuousNumber Travers(NCLBoard *board, const bool& containSPACE);
};

