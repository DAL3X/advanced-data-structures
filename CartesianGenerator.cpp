#include "CartesianGenerator.h"


uint64_t CartesianGenerator::rangeMinimumQuery(std::vector<uint64_t> block, uint64_t min, uint64_t max) {
	//return treeMap_->at(generateCartesianTree(block))->rangeMinimumQuery(min, max);
	// TODO reactivate 
	return min + max;
}



std::string CartesianGenerator::generateCartesianTree(std::vector<uint64_t> numbers) {
	// Use filling and method as proposed on Wikipedia.
	// TODO implement
	return "";
}

void CartesianGenerator::generateAllCartesianTrees(uint64_t vectorSize) {
	// Use filling as proposed on Wikipedia.
	// Set all the RMQ data structures to nullptr. We will fill these in later.
	// TODO implement
	return;
}

CartesianGenerator::CartesianGenerator(std::vector<std::vector<uint64_t>*>* blocks) {
	treeMap_ = new std::unordered_map <std::string, NaiveRMQ*>();
	generateAllCartesianTrees(blocks->at(0)->size()); // The first block is always completely filled and therefore tells us the cartesian tree size
	// TODO Generate NaiveRMQ for every block and insert them into treeMap_.
}

CartesianGenerator::~CartesianGenerator() {
	for (auto pair : *treeMap_) {
		delete pair.second;
	}
	delete treeMap_;
}