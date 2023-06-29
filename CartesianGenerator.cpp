#include "CartesianGenerator.h"
#include "CartesianTree.h"


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
	return min + max;
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
				break;
			}
			else if (currentNode == tree->getRoot()) {
				// Insert as new root
				CartesianNode* newNode = new CartesianNode(numbers[i], nullptr, currentNode, nullptr);
				currentNode->setParent(newNode);
				tree->setRoot(newNode);
				break;
			}
			currentNode = currentNode->getParent();
		}
	}
	fillCartesianTree(tree->getRoot());
	// TODO Transform it to uint64_t format
	return 0;
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