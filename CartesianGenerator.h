#pragma once
#include <unordered_map>
#include "NaiveRMQ.h"

class CartesianGenerator {

private:

	// The map storing all the possible cartesian trees and a corresponding rmq data structure.
	std::unordered_map <uint64_t, NaiveRMQ*>* treeMap_;

	/*
	* Generates the cartesian tree in uint64_t for a given vector of numbers and fills them to give every node existing node 2 leaf children.
	* The filling is needed to make the trees unique (because left/right child matters for cartesian trees!)
	* The filling operation are the ones according to en.wikipedia.org/wiki/Range_minimum_query.
	* (Solution using constant time and linear space)
	* The encoding is according to LOUDS.
	*/ 
	uint64_t generateCartesianTree(std::vector<uint64_t> numbers);

	// Generates all possible cartesian trees for vectors of the given size. This method does not generate the corresponding rqm data structures.
	void generateAllCartesianTrees(uint64_t vectorSize);

public:

	/**
	* Performs a range minimum query by searching for a fitting cartesian tree and delegating the query to the saved rmq data structure.
	* Since all answers are already saved, this should take O(1) time.
	*
	* @param block The block on which this query is performed.
	* @param min The minimum range for the query.
	* @param max The maximum range for the query.
	*/
	uint64_t rangeMinimumQuery(std::vector<uint64_t> block, uint64_t min, uint64_t max);

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