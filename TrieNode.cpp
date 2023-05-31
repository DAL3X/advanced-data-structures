#include "TrieNode.h"


bool TrieNode::isLeaf() {
	return leaf_;
}


TrieNode* TrieNode::getLeftMax() {
	if (!leaf_) {
		return leftMax_;
	}
	return nullptr;
}

TrieNode* TrieNode::previous() {
	if (leaf_) {
		return leftMax_;
	}
	return nullptr;
}


TrieNode* TrieNode::getRightMin() {
	if (!leaf_) {
		return rightMin_;
	}
	return nullptr;
}

TrieNode* TrieNode::next() {
	if (leaf_) {
		return rightMin_;
	}
	return nullptr;
}


BST* TrieNode::getBinarySearchTree() {
	if (leaf_) {
		return tree_;
	}
	return nullptr;
}


TrieNode::TrieNode(TrieNode* leftMax, TrieNode* rightMin) :
	leaf_(false),
	leftMax_(leftMax),
	rightMin_(rightMin) {}

TrieNode::TrieNode(TrieNode* leftMax, TrieNode* rightMin, BST* tree) :
	leaf_(true),
	leftMax_(leftMax),
	rightMin_(rightMin),
	tree_(tree) {}