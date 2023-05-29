#include "BST.h"
#include "Node.h"

	Node* build(std::vector<int64_t> values, int64_t leftRange, int64_t rightRange) {
		if (leftRange > rightRange) {
			return nullptr;
		}
		int64_t split = (leftRange + rightRange) / 2; // This is always an int because of implicit integer rounding
		return new Node(values[split], build(values, leftRange, split-1), build(values, split + 1, rightRange));
	}

	int64_t BST::getPredecessor(int64_t maxSmallerTree) {
		// TODO implement
		return 0;
	}

	Node* BST::getRoot() {
		return root_;
	}

	BST::BST(std::vector<int64_t> values) {
		root_ = build(values, 0, values.size() - 1);
	}