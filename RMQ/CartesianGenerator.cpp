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
			encoded = encoded + (uint64_t) pow(2, encodeIndex);
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
	encoded = encoded + (uint64_t) pow(2, encodeIndex - 1); // Add 1 at the end
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

uint64_t CartesianGenerator::rangeMinimumQuery(uint64_t blockNum, uint64_t min, uint64_t max) {
	return treeMap_->at(blockTrees_->at(blockNum))->rangeMinimumQuery(min, max);
}

uint64_t CartesianGenerator::generateCartesianTree(std::vector<uint64_t>* numbers) {
	CartesianNode* currentNode = new CartesianNode(numbers->at(0), nullptr);
	CartesianTree* tree = new CartesianTree(currentNode);
	for (uint64_t i = 1; i < numbers->size(); i++) {
		while (true) {
			if (currentNode->getValue() <= numbers->at(i)) {
				// Insert as right child and make previous right child the left child of the new node
				CartesianNode* newNode = new CartesianNode(numbers->at(i), currentNode, currentNode->getRightChild(), nullptr);
				if (currentNode->getRightChild() != nullptr) {
					currentNode->getRightChild()->setParent(newNode);
				}
				currentNode->setRightChild(newNode);
				currentNode = newNode;
				break;
			}
			else if (currentNode == tree->getRoot()) {
				// Insert as new root
				CartesianNode* newNode = new CartesianNode(numbers->at(i), nullptr, currentNode, nullptr);
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

CartesianGenerator::CartesianGenerator(std::vector<std::vector<uint64_t>*>* blocks) {
	treeMap_ = new std::unordered_map <uint64_t, NaiveRMQ*>();
	blockTrees_ = new std::vector<uint64_t>();
	for (uint64_t i = 0; i < blocks->size(); i++) {
		uint64_t encodedTree = generateCartesianTree(blocks->at(i));
		treeMap_->insert({ encodedTree, new NaiveRMQ(*(blocks->at(i))) }); // If already present in map, this does nothing. O(1)
		blockTrees_->push_back(encodedTree);
	}
}

CartesianGenerator::~CartesianGenerator() {
	for (auto pair : *treeMap_) {
		delete pair.second;
	}
	delete treeMap_;
}