#pragma once
#include <vector>
#include <cstdint>
#include "CartesianGenerator.h"
#include "LogRMQ.h"

/**
Class for processing rmq queries in O(1) with O(n) space usage.
This is achieved by utilising cartesian trees and their properties towards rmq queries.
We save cartesian trees as a string of variable size instead of a number of fixed size to support queries for arbitrary sizes.
This costs more memory in general, but the memory requirement in the O() notation stays the same.
n is the size of the vector, on which the queries are performed.
*/
class CartesianRMQ {

private:

	// A vector of all blocks in vector format. The last block gets padded with highest the possible number.
	std::vector<std::vector<uint64_t>*>* blocks_;

	// A vector containing the minimal number for every block. It has the same length as blocks_.
	std::vector<uint64_t>* blockMinimum_;

	// A vector containing the position of the minimal number for every block. The position is realtive to the block's beginning! It has the same length as blocks_.
	std::vector<uint64_t>* blockMinimumPos_;

	// Size of one block log_2(totalSize_))/4.
	uint64_t blockSize_;

	// Total size of all original elements that have been divided into blocks WITHOUT the added padding.
	uint64_t totalSize_;

	// Total size of all elements that have been divided into blocks with the added padding.
	uint64_t totalPaddedSize_;

	// The cartesian tree generator used to generate and store all possible cartesian trees for  blocksize_ length.
	CartesianGenerator* treeGenerator_;

	// A log rmq data structure to manage queries over multiple entire blocks.
	LogRMQ* blockRMQ_;

	/**
	* Splits the input array into blocks and saves them in the blocks_ field.
	* Also saves the minimum per block in the blockMinimum_ field.
	*
	* @param numbers The vector of numbers to be split into blocks.
	*/
	void splitInBlocks(std::vector<uint64_t> numbers);

public:

	/**
	* Performs a range minimum query.
	* Since all answers are already saved, this should take O(1) time.
	*
	* @param min The minimum range for the query.
	* @param max The maximum range for the query.
	*/
	int64_t rangeMinimumQuery(uint64_t min, uint64_t max);

	/**
	* Constructs a CartesianRMQ to answer rmq queries in O(1) with O(n) space usage.
	* It adds padding to the numbers if needed and provides the padded vector as input for the generator.
	* 
	* @param numbers The vector of numbers to perform later queries on.
	*/
	CartesianRMQ(std::vector<uint64_t> numbers);

	/**
	* Deconstructs the CartesianRMQ to free all reserved memory.
	*/
	~CartesianRMQ();

};