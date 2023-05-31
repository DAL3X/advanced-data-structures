#include "BST.h"
#include "Node.h"

	/**
	* Recursively builds the Binary Search Tree from left to right
	*/
	Node* build(std::vector<int64_t> values, int64_t leftRange, int64_t rightRange) {
		if (leftRange > rightRange) {
			return nullptr;
		}
		int64_t split = (leftRange + rightRange) / 2; // This is always an integer because of implicit integer rounding
		return new Node(values[split], build(values, leftRange, split-1), build(values, split+1, rightRange));
	}


	/**
	* Recursively finds the predecessor to a given integer in the tree
	*/
	int64_t getPredecessorInternal(Node* node, int64_t maxFound, int64_t limit) {
		if (node == nullptr) {
			// End of tree
			return maxFound;
		}
		if (node->getValue() <= limit && node->getValue() >= maxFound) {
			// Found new maximum
			maxFound = node->getValue();
		}
		if (node->getValue() < limit) {
			// Search in right subtree
			return getPredecessorInternal(node->getRightChild(), maxFound, limit);
		}
		else {
			// Search in left subtree
			return getPredecessorInternal(node->getLeftChild(), maxFound, limit);
		}
	}

	// maxFound is either 0, or the max representant of the left neighbour tree
	int64_t BST::getPredecessor(int64_t maxFound, int64_t limit) {
		return getPredecessorInternal(root_, maxFound, limit);
	}


	Node* BST::getRoot() {
		return root_;
	}


	BST::BST(std::vector<int64_t> values) :
		root_(build(values, 0, values.size() - 1)) {}


	BST::~BST() {
		delete(root_);
	}