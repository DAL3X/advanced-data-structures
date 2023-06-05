#include "YTrie.h"
#include <cmath>
#include <iostream>

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


int64_t getPredecessorInternal(std::unordered_map<std::string, TrieNode*>* lookup, int64_t searchInt, int64_t depth) {
	int64_t leftRange = 0;
	int64_t rightRange = depth;
	return 0;
}

/*
* Adds a leaf to the trie representatives with a max sized binary search tree.
*/
void addRegularTrieLeaf(std::vector<int64_t> values, int64_t index, std::vector<TrieNode*>* representatives, int64_t depth) {
	int64_t maxIndex = values.size() - 1;
	if (index == depth - 1) {
		// First to add has nullptr as previous
		representatives->push_back(new TrieNode(values[index], nullptr, constructBST(index, depth, values)));
	}
	else {
		// All other representatives have the predecessor as previous. Also sets the next pointers for the last added leaf.
		representatives->push_back(new TrieNode(values[index], representatives->back(), constructBST(index, depth, values)));
		(*representatives)[representatives->size() - 2]->setNext((*representatives)[representatives->size() - 1]);
	}
}

/*
* Adds a leaf to the trie representatives without a max sized binary search tree. This can only happen, when the split is imperfect.
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
void YTrie::constructTrie(std::vector<TrieNode*>* representatives, std::vector<int64_t>* representativeValues,
	int64_t exponent, std::string bitHistory, int64_t leftRange, int64_t rightRange) {
	int64_t split = 1LL << exponent; // Mask is 2^maskShift
	if (exponent != -1) { // Construct inner node
		int64_t splitIndex = rightRange + 1;
		TrieNode* leftMax = nullptr;
		TrieNode* rightMin = nullptr;
		bool foundSplit = false; 
		// Attempt to find a split point
		for (int64_t i = leftRange; i <= rightRange; i++) {
			if ((*representativeValues)[i] >= split) { // Found split point
				if (!foundSplit) { // Found split point for the first time
					splitIndex = i;
					foundSplit = true;
					if (i != leftRange) {
						leftMax = (*representatives)[i - 1];
					}
					rightMin = (*representatives)[i];
				}
				(*representativeValues)[i] = (*representativeValues)[i] - split;
			}
		}
		if (leftMax == nullptr && rightMin == nullptr) { // No split was found, all representant belong to the left side of this inner node
			leftMax = (*representatives)[rightRange];
		}
		TrieNode* node = new TrieNode(leftMax, rightMin);
		lookup_.insert({ bitHistory, node });
		if (splitIndex > leftRange) { // Construct left subtree
			std::string leftMaskHistory = bitHistory;
			constructTrie(representatives, representativeValues, exponent - 1, leftMaskHistory.append("0"), leftRange, splitIndex - 1);
		}
		if (splitIndex <= rightRange) { // Construct right subtree
			std::string rightMaskHistory = bitHistory;
			constructTrie(representatives, representativeValues, exponent - 1, rightMaskHistory.append("1"), splitIndex, rightRange);
		}
	}
	else { // Add the leafs
		if ((bitHistory.compare(bitHistory.size(), 1, "0")) == 0) {
			lookup_.insert({ bitHistory, (*representatives)[leftRange] });
		}
		else {
			lookup_.insert({ bitHistory, (*representatives)[rightRange] });
		}
	}
}


YTrie::YTrie(std::vector<int64_t> values) :
	depth_(calcDepth(values)) {
	split(values);
	std::vector<int64_t> representativeValues;
	for (int i = 0; i < representatives_.size(); i++) {
		representativeValues.push_back(representatives_[i]->getValue());
	}
	constructTrie(&representatives_, &representativeValues, depth_, "", 0, (representatives_.size() - 1));
}


int64_t YTrie::getPredecessor(int64_t limit) {

	return 0;
}

std::vector<TrieNode*> YTrie::getTestRep() {
	return representatives_;
}

std::unordered_map<std::string, TrieNode*>* YTrie::getTestTrie() {
	return &lookup_;
}