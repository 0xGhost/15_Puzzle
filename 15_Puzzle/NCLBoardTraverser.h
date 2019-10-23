// Author: Yiang Lu
// Date created: 15/Oct/2019
#pragma once
#include "NCLBoard.h"
#include <unordered_set>
#include "ctpl_stl.h"
#include <mutex>
#include <shared_mutex>

using std::string;
using std::unordered_set;

namespace std {
	// customize hash function for a vector<char>
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

class NCLBoardTraverser
{
public:
	NCLBoardTraverser(NCLBoard* board, const bool& containSPACE); 
	
	ContinuousNumber GetTotalContinuousNumber() { return totalContinuousNumber; }
private:
	int size;
	unordered_set<vector<char>> boardSet; // the history of searching
	ContinuousNumber totalContinuousNumber; // output result
	static ctpl::thread_pool thPool;
	mutable std::shared_mutex historyMutex;
	ContinuousNumber Travers(NCLBoard *board, const bool& containSPACE); // search all possible move and check continuous for all vaild turn
};

