#pragma once
#include <cstdint>
#include <memory>

class Node {
public:
	Node& getLeftChild();
	Node& getRightChild();
	int64_t getValue();

	Node(int64_t value, Node& leftNode, Node& rightNode);
};