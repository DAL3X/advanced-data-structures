#pragma once
#include <cstdint>
#include "BST.h"

class TrieNode {

private:
	bool leaf_ = false;
	// These are always set. For leaves, they represent the previous and next pointer in the double linked list.
	TrieNode* leftMax_ = nullptr;
	TrieNode* rightMin_= nullptr;

	BST* tree_ = nullptr; // This is only set for a leaf, else nullptr.
	int64_t value_ = LLONG_MAX; // Set to max so predecessor queries fail when not set

public:
	bool isLeaf();
	int64_t getValue();
	TrieNode* getLeftMax();
	TrieNode* getRightMin();
	TrieNode* previous();
	TrieNode* next();
	void setNext(TrieNode* next);
	BST* getBinarySearchTree();
	TrieNode(TrieNode* leftMax, TrieNode* rightMin);	// For inner nodes
	TrieNode(int64_t value, TrieNode* previous, BST* tree);			// For leaves

};