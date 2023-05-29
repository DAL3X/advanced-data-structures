#pragma once
#include <cstdint>

class Node {

private:
	std::int64_t value_ = 0;
	Node* left_ = nullptr;
	Node* right_ = nullptr;

public:
	Node* getLeftChild();
	Node* getRightChild();
	int64_t getValue();

	Node(int64_t value, Node* leftNode, Node* rightNode);
};