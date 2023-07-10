#pragma once
#include <cstdint>
#include <climits>
#include "BST.h"

/**
* Class representing a node in the trie. 
* It fulfills two purposes at once.
* Inner Trie nodes only know the leftMax and rightMin nodes, to support efficient predecessor queries.
* Outer Trie nodes (leaves) know the left and right leaf neighbours and form an implicit linked list. They also hold a value.
*/
class TrieNode {

private:
	bool leaf_ = false;

	// These are always set. For leaves, they represent the previous and next pointer in the double linked list.
	TrieNode* leftMax_ = nullptr;
	TrieNode* rightMin_= nullptr;

	// This is only set for a leaf, else nullptr.
	BST* tree_ = nullptr; 

	// Set to max so predecessor queries fail when not set.
	uint64_t value_ = ULLONG_MAX;

public:

	bool isLeaf();

	/**
	* Only for leaves!
	* Using it on inner nodes returns the maximum possible integer.
	*/
	uint64_t getValue();

	/**
	* Only for inner nodes!
	* Returns the leaf with the maximum value on the left side.
	* Does the same as previous(), but should only be used on inner nodes for clarity.
	*/
	TrieNode* getLeftMax();

	/**
	* Only for inner nodes!
	* Returns the leaf with the minimum value on the right side.
	* Does the same as next(), but should only be used on inner nodes for clarity.
	*/
	TrieNode* getRightMin();

	/**
	* Only for leaves!
	* Returns the left leaf neighbour.
	* Does the same as getLeftMax(), but should only be used on leaves for clarity.
	*/
	TrieNode* previous();

	/**
	* Only for leaves!
	* Returns the right leaf neighbour.
	* Does the same as getRightMin(), but should only be used on leaves for clarity.
	*/
	TrieNode* next();

	/**
	* Only for leaves!
	* Sets the right neighbour leaf.
	*/
	void setNext(TrieNode* next);

	/**
	* Only for leaves!
	* Returns the binary search tree corresponding to this trie leaf.
	*/
	BST* getBinarySearchTree();

	/**
	* Constructs an inner node.
	*/
	TrieNode(TrieNode* leftMax, TrieNode* rightMin);

	/**
	* Constructs a leaf. 
	* Next cannot be set here, since the nodes are generated from left to right.
	*/
	TrieNode(uint64_t value, TrieNode* previous, BST* tree);

};