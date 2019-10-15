#pragma once
#include "NCLBoard.h"
#include <set>
#include <unordered_map>
#include <unordered_set>

using std::set;
using std::string;
using std::unordered_map;
using std::unordered_set;

namespace std {
	template <>
	struct hash<std::vector<int>> {
		size_t operator()(const vector<int>& v) const {
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
	NCLBoardTraverser();
	~NCLBoardTraverser();

	ContinuousNumber Travers(NCLBoard *board);
	ContinuousNumber GetTotalContinuousNumber() { return totalContinuousNumber; }
private:
	Node* root = nullptr;
	int size;
	unordered_map<string, NCLBoard*> hashMap;
	unordered_set<vector<int>> boardSet;
	bool Search(const NCLBoard* board);
	ContinuousNumber totalContinuousNumber;
};

