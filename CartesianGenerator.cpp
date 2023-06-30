#include "CartesianGenerator.h"
#include "CartesianTree.h"
#include <queue>
#include <cmath>



/**
* Encodes a cartesian tree using LOUDS, but starting from the LSB instead of MSB and adding a 1 at the very end (MSB).
* We add a 1 to distinguish between 0s representing the last recorded nodes and 0s of not filled bits.
* LOUDS uses 2n+1 (2n+2 with modification) bits to encode a tree with n nodes.
* This means we can support trees with up to 31 nodes, which should enough considering the size of a block (even with the fill step).
*/
uint64_t encodeTree(CartesianTree* tree) {
	uint64_t encoded = 0x1; // 10 start for LOUDS.
	uint64_t encodeIndex = 2; // 2, because first two bits are already filled with 10.
	std::queue<CartesianNode*> queue;
	queue.push(tree->getRoot());
	while (!queue.empty()) { // Breadth first search.
		CartesianNode* node = queue.front();
		queue.pop();
		// Add 1s corresponding to number of children
		for (uint64_t childIndex = 0; childIndex < node->getNumberChildren(); childIndex++) {
			encoded = encoded + pow(2, encodeIndex);
			encodeIndex++;
		}
		encodeIndex++;// Add 0.
		if (node->getLeftChild() != nullptr) { // Push left before right child, because we are traversing left to right.
			queue.push(node->getLeftChild());
		}
		if (node->getRightChild() != nullptr) {
			queue.push(node->getRightChild());
		}
	}
	encoded = encoded + pow(2, encodeIndex - 1); // Add 1 at the end
	return encoded;
}

/**
* Fills the tree corresponding to this root with extra leaves as suggested in en.wikipedia.org/wiki/Range_minimum_query.
* (Solution using constant time and linear space)
* This is needed to make child on the left/right side of a nodes distinguishable.
*/
void fillCartesianTree(CartesianNode* node) {
	if (node->getLeftChild() == nullptr) {
		node->setLeftChild(new CartesianNode(ULLONG_MAX, node));
	}
	else {
		fillCartesianTree(node->getLeftChild());
	}
	if (node->getRightChild() == nullptr) {
		node->setRightChild(new CartesianNode(ULLONG_MAX, node));
	}
	else {
		fillCartesianTree(node->getRightChild());
	}
}

uint64_t CartesianGenerator::rangeMinimumQuery(std::vector<uint64_t> block, uint64_t min, uint64_t max) {
	//return treeMap_->at(generateCartesianTree(block))->rangeMinimumQuery(min, max);
	// TODO reactivate 
	return generateCartesianTree(block);
}

uint64_t CartesianGenerator::generateCartesianTree(std::vector<uint64_t> numbers) {
	CartesianNode* currentNode = new CartesianNode(numbers[0], nullptr);
	CartesianTree* tree = new CartesianTree(currentNode);
	for (uint64_t i = 1; i < numbers.size(); i++) {
		while (true) {
			if (currentNode->getValue() <= numbers[i]) {
				// Insert as right child and make previous right child the left child of the new node
				CartesianNode* newNode = new CartesianNode(numbers[i], currentNode, currentNode->getRightChild(), nullptr);
				if (currentNode->getRightChild() != nullptr) {
					currentNode->getRightChild()->setParent(newNode);
				}
				currentNode->setRightChild(newNode);
				currentNode = newNode;
				break;
			}
			else if (currentNode == tree->getRoot()) {
				// Insert as new root
				CartesianNode* newNode = new CartesianNode(numbers[i], nullptr, currentNode, nullptr);
				currentNode->setParent(newNode);
				tree->setRoot(newNode);
				currentNode = newNode;
				break;
			}
			currentNode = currentNode->getParent();
		}
	}
	fillCartesianTree(tree->getRoot()); // Fill first
	uint64_t encodedTree = encodeTree(tree); // Then encode
	return encodedTree;
}

void CartesianGenerator::generateAllCartesianTrees(uint64_t vectorSize) {
	// Use filling as proposed on Wikipedia.
	// Set all the RMQ data structures to nullptr. We will fill these in later.
	// TODO implement
	return;
}

CartesianGenerator::CartesianGenerator(std::vector<std::vector<uint64_t>*>* blocks) {
	treeMap_ = new std::unordered_map <uint64_t, NaiveRMQ*>();
	generateAllCartesianTrees(blocks->at(0)->size()); // The first block is always completely filled and therefore tells us the cartesian tree size
	// TODO Generate NaiveRMQ for every block and insert them into treeMap_.
}

CartesianGenerator::~CartesianGenerator() {
	for (auto pair : *treeMap_) {
		delete pair.second;
	}
	delete treeMap_;
}