#include "YTrie.h"
#include <cmath>

/*
* Since the numbers are max 64 bits, we could just assume depth = 64.
* But we can speed up the process when only smaller numbers are present.
* Eg. with only 32 bit numbers or smaller, we can half the depth of the Trie.
* The depth is given as the number of bits used to represent the largest number in the input values.
*/
int64_t calcDepth(std::vector <int64_t> values) {
	return (int64_t)std::floor(std::log2(values.back()));
}

BST* constructBST(int64_t position, int64_t groupSize, std::vector <int64_t> values) {
	// Isolate the group with the given size for the representative on the given position 
	std::vector<int64_t> group(values.begin() + position - (groupSize - 1), values.begin() + position + 1);
	BST* tree = new BST(group);
	return tree;
}

/*
* Adds a leaf to the trie with a max sized binary search tree.
*/
void addRegularTrieLeaf(std::vector<int64_t> values, int64_t index, std::vector<TrieNode*>* representatives, int64_t depth) {
	int64_t maxIndex = values.size() - 1;
	if (index == depth - 1) {
		// First to add has nullptr as previous
		representatives->push_back(new TrieNode(values[index], nullptr, constructBST(index, depth, values)));
	}
	else {
		// All the others have the predecessor as previous. Also sets the next pointers for the last added leaf.
		representatives->push_back(new TrieNode(values[index], representatives->back(), constructBST(index, depth, values)));
		(*representatives)[representatives->size() - 2]->setNext((*representatives)[representatives->size() - 1]);
	}
}

/*
* Adds a leaf to the trie without a max sized binary search tree. This can only happen, when the split is imperfect.
*/
void addIrregularTrieLeaf(std::vector<int64_t> values, std::vector<TrieNode*>* representatives, int64_t depth) {
		representatives->push_back(new TrieNode(values.back(), representatives->back(), constructBST(values.size() - 1, values.size() % depth, values)));
		(*representatives)[representatives->size() - 2]->setNext((*representatives)[representatives->size() - 1]);
}



void YTrie::split(std::vector <int64_t> values) {
	for (int64_t i = depth_ - 1; i < values.size(); i = i + depth_) {
		// Store the representative and construct the BST for it.
		addRegularTrieLeaf(values, i, &representatives_, depth_);
	}
	if (values.size() % depth_ != 0) {
		// One or more(<depth) values at the back don't have a representant yet. Take the last value as one and construct the BST.
		addIrregularTrieLeaf(values, &representatives_, depth_);
	}
}

/*
* 0 left, 1 right
*/
void YTrie::constructTrie(std::vector<TrieNode*>* representatives, int64_t maskShift, int64_t maskHistory, int64_t leftRange, int64_t rightRange) {
	int64_t split = 1LL << maskShift; // Mask is 2^maskShift
	if (maskShift != 0) {
		TrieNode* leftMax = nullptr;
		TrieNode* rightMin = nullptr;
		for (int64_t i = leftRange; i <= rightRange; i++) { // This for loop could also be replaced by using binary search to find the split point.
			if ((*representatives)[i]->getValue() >= split) {
				// Found split point
				if (i != leftRange) {
					leftMax = (*representatives)[i - 1];
				}
				if (i != rightRange) {
					rightMin = (*representatives)[i];
				}
				break;
			}
		}
		TrieNode* node = new TrieNode(leftMax, rightMin);
		lookup_.insert({ maskHistory + split, node });
		constructTrie(representatives, maskShift - 1, maskHistory + split, leftRange, i-1);
		constructTrie(representatives, maskShift - 1, maskHistory + split, i, rightRange);
	}
	else {
		// Add the leaves
	}
}


YTrie::YTrie(std::vector<int64_t> values) :
	depth_(calcDepth(values)) {
	split(values);
	constructTrie(&representatives_, depth_, 0, 0, values.size() - 1);
}


int64_t YTrie::getPredecessor(int64_t limit) {
	return 0;
}

std::vector<TrieNode*> YTrie::getTestRep() {
	return representatives_;
}