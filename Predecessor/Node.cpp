#include "Node.h"


	Node* Node::getLeftChild() {
		return left_;
	}


	Node* Node::getRightChild() {
		return right_;
	}


	uint64_t Node::getValue() {
		return value_;
	}


	Node::Node(uint64_t value, Node* left, Node* right):
		value_(value),
		left_(left),
		right_(right) {}


	Node::~Node() {
		// delete on a non reserved block of memory has undefined behaviour, hence we check for a nullptr first.
		if (left_ != nullptr) {
			delete(left_);
		}
		if (right_ != nullptr) {
			delete(right_);
		}
	}
