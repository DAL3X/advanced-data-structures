#pragma once
#include <cstdint>
#include "BST.h"

class TrieNode {

private:
	bool leaf_ = false;
	// These are always set. For leaves, they represent the previous and next pointer in the double linked list.
	TrieNode* leftMax_ = nullptr;
	TrieNode* rightMin_= nullptr;
	// This is only set for a leaf, else nullptr.
	BST* tree_ = nullptr;

public:
	bool isLeaf();
	TrieNode* getLeftMax();
	TrieNode* getRightMin();
	TrieNode* previous();
	TrieNode* next();
	BST* getBinarySearchTree();
	TrieNode(TrieNode* leftMax, TrieNode* rightMin);			// For inner nodes
	TrieNode(TrieNode* leftMax, TrieNode* rightMin, BST* tree); // For leaves

};