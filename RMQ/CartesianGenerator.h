#pragma once
#include <unordered_map>
#include "NaiveRMQ.h"

class CartesianGenerator {

private:

	// The map storing all the possible cartesian trees and a corresponding rmq data structure.
	std::unordered_map <uint64_t, NaiveRMQ*>* treeMap_;

	// A vector containing the cartesian trees for all blocks. Access is handled with the block index.
	std::vector<uint64_t>* blockTrees_;

	/*
	* Generates the cartesian tree for a given vector of numbers and fills them to give every node exactly 2 children.
	* The filling is needed to make the trees unique (because left/right child matters for cartesian trees!)
	* The filling operation are the ones according to en.wikipedia.org/wiki/Range_minimum_query.
	* (Solution using constant time and linear space)
	* The encoding is according to LOUDS.
	*/ 
	uint64_t generateCartesianTree(std::vector<uint64_t>* numbers);

public:

	/**
	* Performs a range minimum query by searching for a fitting cartesian tree and delegating the query to the saved rmq data structure.
	* Since all answers are already saved, this should take O(1) time.
	*
	* @param blockNum Index of the block in which the query is performed.
	* @param min The minimum range for the query.
	* @param max The maximum range for the query.
	*/
	uint64_t rangeMinimumQuery(uint64_t blockNum, uint64_t min, uint64_t max);

	/**
	* Construct a CartesianGenerator for the given blocks.
	* The blocks all have to be the same size!
	* 
	* @param blocks The vector of vectors representing all blocks.
	*/
	CartesianGenerator(std::vector<std::vector<uint64_t>*>* blocks);

	/**
	* Deconstructs the CartesianGenerator to free up all reserved memory.
	*/
	~CartesianGenerator();
};