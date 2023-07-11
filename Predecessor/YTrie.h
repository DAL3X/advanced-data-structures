#pragma once
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <string>
#include "TrieNode.h"

/**
* Implementation of a Y-Trie.
* The trie itself is just built on representatives of blocks.
* The inner trie nodes have pointers to answer predecessor queries, while the trie leaves have binary searching trees over all values.
* To quickly traverse the trie, a HashMap is used.
*/
class YTrie {

private:
	// Depth of the trie.
	uint64_t depth_;

	// Vector of corresponding representants for all provided values.
	std::vector<TrieNode*> representatives_ = *(new std::vector<TrieNode*>);

	// HashMap for performing a binary search on trie levels.
	std::unordered_map<std::string, TrieNode*> lookup_ = *(new std::unordered_map<std::string, TrieNode*>);

	// Minimal value in this trie. Used for lower boundary detection.
	uint64_t minimalValue_;

	/**
	* Splits the given values into their representatives and creates TrieNodes for them.
	* They are then linked to obtain the "leaf level" for our final trie.
	*/
	void split(std::vector <uint64_t> values);

	/**
	* Constructs the trie by creating all inner trie nodes and putting them into the lookup_ HashMap for later use.
	* This is achieved by checking for a 0, or a 1 at a specific bit position.
	* If we subtract 2^position from all numbers that have a 1 on that position every time we do it, this task changes.
	* We can now check for greater equal 2^position and split on the first point, where this condition is met.
	* All nodes representatives smaller than that split, have a 0 on this position and all others a 1.
	* leftMax is the value left of the split point and rightMin the split point itself.
	* We track the history by adding a "0" or a "1" to the bit history string and add the inner nodes in our HashMap.
	* In the end, we also add the representatives themselves to the HashMap in order to allow direct hits on leaves.
	* 
	* @param representatives A pointer to the TrieNode vector containing all the linked leaves.
	* @param representativeValues A vector containing only the values of the representatives. This is needed, since we subtract from values and need to store the remainder.
	* @param exponent The position on which we check for a 0 or 1. Starts at depth of trie.
	* @param bitHistory The history of 0 and 1 edges to reach this inner node we are constructing. Starts with empty string.
	* @param leftRange The left border to check for splitting points. Starts at 0.
	* @param rightRange The right border to check for splitting points. Starts at representatives length.
	*/
	void constructTrie(std::vector<TrieNode*>* representatives, int64_t exponent, std::string bitHistory, uint64_t leftRange, uint64_t rightRange);

public:
	/**
	* Constructs and prepares the Y-Trie initialized with the given values.
	*/
	YTrie(std::vector<uint64_t> values);

	/**
	* Performs the predecessor query.
	* This is done by transforming the input into a bitset and the bitset into a string.
	* We can then perform a binary search on the lookup_ HashMap to find the best fitting node.
	* Follow the leftMax, or rightMin and previous pointer to get the best fitting leave.
	* Trie leaves have a binary search tree, which can then be used to search for the predecessors in all values (not just representants).
	* 
	* @param limit The number we want to find the predeccesor of.
	*/
	uint64_t getPredecessor(uint64_t limit);
};