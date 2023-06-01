#pragma once
#include <cstdint>
#include <vector>
#include <unordered_map>
#include "TrieNode.h"

class YTrie {

private:
	int64_t depth_;
	std::vector<TrieNode*> representatives_ = *(new std::vector<TrieNode*>);
	std::unordered_map<int64_t, TrieNode*> lookup_ = *(new std::unordered_map<int64_t, TrieNode*>);
	void split(std::vector <int64_t> values);
	void constructTrie(std::vector<TrieNode*>* representatives, int64_t maskShift, int64_t maskHistory, int64_t leftRange, int64_t rightRange);

public:
	YTrie(std::vector<int64_t> values);
	int64_t getPredecessor(int64_t limit);
	std::vector<TrieNode*> getTestRep();
	std::unordered_map<int64_t, TrieNode*>* getTestTrie();
};