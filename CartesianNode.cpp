#include "CartesianNode.h"

CartesianNode::CartesianNode(uint64_t value, CartesianNode* parent, CartesianNode* left, CartesianNode* right) :
	value_(value),
	left_(left),
	right_(right),
	parent_(parent) {}


CartesianNode::~CartesianNode() {
	// delete on a non reserved block of memory has undefined behaviour, hence we check for a nullptr first.
	if (left_ != nullptr) {
		delete(left_);
	}
	if (right_ != nullptr) {
		delete(right_);
	}
	if (parent_ != nullptr) {
		delete parent_;
	}
}

CartesianNode::CartesianNode(uint64_t value, CartesianNode* parent) :
	value_(value),
	parent_(parent) {}

CartesianNode* CartesianNode::getLeftChild() {
	return left_;
}

CartesianNode* CartesianNode::getRightChild() {
	return right_;
}

CartesianNode* CartesianNode::getParent() {
	return parent_;
}

uint64_t CartesianNode::getValue() {
	return value_;
}

void CartesianNode::setLeftChild(CartesianNode* node) {
	left_ = node;
}

void CartesianNode::setRightChild(CartesianNode* node) {
	right_ = node;
}

void CartesianNode::setParent(CartesianNode* node) {
	parent_ = node;
}