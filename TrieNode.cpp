#include "TrieNode.h"


bool TrieNode::isLeaf() {
	return leaf_;
}


uint64_t TrieNode::getValue() {
	return value_;
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

void TrieNode::setNext(TrieNode* next) {
	rightMin_ = next;
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

TrieNode::TrieNode(uint64_t value, TrieNode* previous, BST* tree) :
	leaf_(true),
	value_(value),
	leftMax_(previous),
	tree_(tree) {}