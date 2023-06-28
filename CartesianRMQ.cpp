#include "CartesianRMQ.h"
#include <cmath>

void CartesianRMQ::splitInBlocks(std::vector<uint64_t> numbers) {
	uint64_t numBlocks = totalPaddedSize_ / blockSize_;
	for (uint64_t i = 0; i < numBlocks; i++) {
		std::vector<uint64_t>* block = new std::vector<uint64_t>(numbers.begin() + (i * blockSize_), numbers.begin() + (i * blockSize_) + blockSize_);
		blocks_->push_back(block);
		// Now find min and position of min
		uint64_t minimum = block->at(0);
		uint64_t position = 0;
		for (uint64_t i = 1; i < block->size(); i++) {
			if (block->at(i) < minimum) {
				minimum = block->at(i);
				position = i; // Position is relative to block start and needs to be transformed before use.
			}
		}
		blockMinimum_->push_back(minimum);
		blockMinimumPos_->push_back(position);
	}
}

int64_t CartesianRMQ::rangeMinimumQuery(uint64_t min, uint64_t max) {
	uint64_t minBorder = (uint64_t)floor(min / blockSize_);
	uint64_t maxBorder = (uint64_t)floor(max / blockSize_);
	uint64_t queryOne, queryTwo, queryThree = ULLONG_MAX;
	if (min % blockSize_ != 0) { // We have a left subquery that we have to answer with cartesian trees.
		queryOne = treeGenerator_->rangeMinimumQuery(*(blocks_->at(minBorder)), min - blockSize_ * minBorder, blockSize_ - 1);
		minBorder++;
	}
	if ((max+1) % blockSize_ != 0) { // We have a right subquery that we have to answer with cartesian trees.
		queryTwo = treeGenerator_->rangeMinimumQuery(*(blocks_->at(maxBorder)), 0, max - blockSize_ * maxBorder);
		maxBorder--;
	}
	if (minBorder <= maxBorder) {
		uint64_t minBlockNum = blockRMQ_->rangeMinimumQuery(minBorder, maxBorder);
		queryThree = blockMinimumPos_->at(minBlockNum) + minBlockNum * blockSize_; // Recieve and transform position of minimal number in found minimal block.
	}

	return std::min({ queryOne, queryTwo, queryThree });
}

CartesianRMQ::CartesianRMQ(std::vector<uint64_t> numbers) {
	blocks_ = new std::vector<std::vector<uint64_t>*>();
	blockMinimum_ = new std::vector<uint64_t>();
	blockMinimumPos_ = new std::vector<uint64_t>();
	totalSize_ = numbers.size();
	blockSize_ = (int64_t)std::ceil(std::log2(totalSize_) / 4); // s = ceil(log(n)/4)
	if (totalSize_ % blockSize_ != 0) { // Check for padding
		uint64_t toFill = blockSize_ - (totalSize_ % blockSize_); // Tells us how many spaces we must fill
		for (uint64_t i = 0; i < toFill; i++) {
			numbers.push_back(ULLONG_MAX); // Push back the max numbers, so minima queries still work in the last block.
		}
	}
	totalPaddedSize_ = numbers.size();
	splitInBlocks(numbers);
	blockRMQ_ = new LogRMQ(*blockMinimum_);
	treeGenerator_ = new CartesianGenerator(blocks_);
}

CartesianRMQ::~CartesianRMQ() {
	for (uint64_t i = 0; i < blocks_->size(); i++) {
		delete blocks_->at(i);
	}
	delete blocks_;
	delete treeGenerator_;
}