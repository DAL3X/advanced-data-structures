#pragma once
#include "Node.h"
#include <cstdint>
#include <vector>

class BST {

private:
	Node* root_ = nullptr;

public:
	int64_t getPredecessor(int64_t maxSmallerTree, int64_t limit);
	Node* getRoot();
	BST(std::vector<int64_t> values);
	~BST();
};