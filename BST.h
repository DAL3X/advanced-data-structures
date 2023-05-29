#pragma once
#include "Node.h"
#include <cstdint>
#include <vector>

class BST {

private:
	Node* root_;

public:
	int64_t getPredecessor(int64_t maxSmallerTree);
	Node* getRoot();
	BST(std::vector<int64_t> values);
};