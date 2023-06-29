#include "CartesianTree.h"

CartesianTree::CartesianTree(CartesianNode* root):
	root_(root) {}

CartesianNode*  CartesianTree::getRoot() {
	return root_;
}

void CartesianTree::setRoot(CartesianNode* node) {
	root_ = node;
}

CartesianTree::~CartesianTree() {
	if (root_ != nullptr) {
		delete root_;
	}
}