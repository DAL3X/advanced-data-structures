#pragma once
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <string>
#include "TrieNode.h"

class YTrie {

private:
	int64_t depth_;
	std::vector<TrieNode*> representatives_ = *(new std::vector<TrieNode*>);
	std::unordered_map<std::string, TrieNode*> lookup_ = *(new std::unordered_map<std::string, TrieNode*>);
	void split(std::vector <int64_t> values);
	void constructTrie(std::vector<TrieNode*>* representatives, std::vector<int64_t>* representativeValues, int64_t exponent, std::string bitHistory, int64_t leftRange, int64_t rightRange);

public:
	YTrie(std::vector<int64_t> values);
	int64_t getPredecessor(int64_t limit);
};