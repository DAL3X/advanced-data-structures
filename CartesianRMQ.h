#pragma once
#include <vector>
#include <cstdint>
#include "CartesianGenerator.h"

/**
Class for processing rmq queries in O(1) with O(n) space usage.
This is achieved by utilising cartesian trees and their properties towards rmq queries.
n is the size of the vector, on which the queries are performed.
*/
class CartesianRMQ {

private:

	// A vector of all blocks in vector format.	
	std::vector<std::vector<uint64_t>*>* blocks_;

	// Size of one block (floor(log_2(totalSize_))/4).
	uint64_t blockSize_;

	// Total size of all elements that have been divided into blocks.
	uint64_t totalSize_;

	// The cartesian tree generator used to generate and store all possible cartesian trees for  blocksize_ length.
	CartesianGenerator treeGenerator_;

	/**
	* Splits the input array into blocks and saves them in the blocks_ attribute.
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
	* 
	* @param numbers The vector of numbers to perform later queries on.
	*/
	CartesianRMQ(std::vector<uint64_t> numbers);

	/**
	* Deconstructs the CartesianRMQ to free all reserved memory.
	*/
	~CartesianRMQ();

};