#pragma once
#include <cstdint>
#include <vector>
#include <unordered_map>
#include "TrieNode.h"

class YTrie {

private:
	int64_t depth_;
	std::vector<int64_t> representatives_ = *(new std::vector<int64_t>);
	std::vector<std::unordered_map<int64_t, TrieNode>*> lookup_ = *(new std::vector<std::unordered_map<int64_t, TrieNode>*>);
	std::unordered_map<int64_t, BST*> searchTrees_ = *(new std::unordered_map<int64_t, BST*>);
	void split(std::vector <int64_t> values);
	void constructBST(int64_t position, int64_t groupSize, std::vector <int64_t> values);

public:
	YTrie(std::vector<int64_t> values);
	int64_t getPredecessor(int64_t limit);
	BST* getTestTree(int64_t rep);
	std::vector<int64_t> getTestRep();
};