#include "BST.h"
#include "Node.h"
#include <cmath>

	/**
	* Recursively builds the Binary Search Tree from left to right.
	* Since the given values are sorted, we can split the array and the subarrays in the middle.
	* 
	* @param values all the values, on which the binary search tree should be constructed.
	* @param leftRange Left border for recursive construction. Starts at 0.
	* @param rightRange Right border for recursive construction. Starts at values.size().
	*/
	Node* build(std::vector<uint64_t> values, int64_t leftRange, int64_t rightRange) {
		if (leftRange > rightRange) {
			return nullptr;
		}
		int64_t split = round((leftRange + rightRange) / 2);
		return new Node(values[split], build(values, leftRange, split-1), build(values, split+1, rightRange));
	}


	/**
	* Recursively finds the predecessor to a given integer in the tree.
	* This is done by comparing to the value in the node and then looking at the left, or right child.
	* 
	* @params node The node we are looking at right now. Starts at the root.
	* @params maxFound The best predecessor candidate found so far. Starts with root's value.
	* @param limit The number we want to find the predecessor for.
	*/
	int64_t getPredecessorInternal(Node* node, uint64_t maxFound, uint64_t limit) {
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

	uint64_t BST::getPredecessor(uint64_t maxFound, uint64_t limit) {
		return getPredecessorInternal(root_, maxFound, limit);
	}


	Node* BST::getRoot() {
		return root_;
	}


	BST::BST(std::vector<uint64_t> values) :
		root_(build(values, 0, values.size() - 1)) {}


	BST::~BST() {
		delete(root_);
	}