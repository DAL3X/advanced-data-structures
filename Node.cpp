#include "Node.h"

	Node* Node::getLeftChild() {
		return left_;
	}

	Node* Node::getRightChild() {
		return right_;
	}

	int64_t Node::getValue() {
		return value_;
	}

	Node::Node(int64_t value, Node* left, Node* right):
		value_(value),
		left_(left),
		right_(right_) {}
