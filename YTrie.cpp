#include "YTrie.h"
#include <cmath>

/**
* Since the numbers are max 64 bits, we could just assume depth = 64.
* But we can speed up the process when only smaller numbers are present.
* Eg. with only 32 bit numbers or smaller, we can half the depth of the Trie.
* The depth is given as the number of bits used to represent the largest number in the input values.
*/
int64_t calcDepth(std::vector <int64_t> values) {
	return (int64_t)std::floor(std::log2(values.back()));
}


void YTrie::split(std::vector <int64_t> values) {
	for (int64_t i = depth_ - 1; i < values.size(); i = i + depth_) {
		// Store the representative and construct the BST for it
		representatives_.push_back(values[i]);
		constructBST(i, depth_, values);
	}
	if (values.size() % depth_ != 0) {
		// One or more(<depth) values at the back don't have a representant yet. Take the last value as one and construct the BST
		representatives_.push_back(values.back());
		constructBST(values.size()-1, values.size() % depth_, values);
	}
}


/**
* Constructs a Binary Search Tree for given Parameters. This is part of the lower Y-Trie implementation.
*/
void YTrie::constructBST(int64_t position, int64_t groupSize, std::vector <int64_t> values) {
	// Isolate the group with the given size for the representative on the given position 
	std::vector<int64_t> group(values.begin() + position - (groupSize-1), values.begin() + position + 1);
	BST* tree = new BST(group);
	searchTrees_.insert({values[position], tree});
}


YTrie::YTrie(std::vector<int64_t> values) :
	depth_(calcDepth(values)) {
	split(values);
}


int64_t YTrie::getPredecessor(int64_t limit) {
	return 0;
}

BST* YTrie::getTestTree(int64_t rep) {
	return searchTrees_[rep];
}

std::vector<int64_t> YTrie::getTestRep() {
	return representatives_;
}