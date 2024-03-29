#pragma once
#include <cstdint>
#include <vector>

/**
Class for naively storing RMQ answers and processing the queries in O(1) with O(n^2) space usage.
n is the size of the vector, on which the queries are performed.
*/
class NaiveRMQ {

private:

	// Vector used as a 2D vector for saving all answers.
	std::vector<uint64_t>* savedAnswers;
	
	// Size of the array that was given to the constructor. Needed for 2D access in the 1D vector.
	uint64_t size;

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
	* Constructor for the NaiveRMQ class.
	* Takes a vector of all numbers and naively generates and saves all answers for all possible range minimum queries on the heap.
	* This takes O(n^2) space, with n being the size of the given array.
	* The answers are saved in a 1D vector, which functions like a 2D vector by splitting it into n blocks of size n. 
	*
	* @param numbers The vector of numbers on which the rmq queries should be possible.
	*/
	NaiveRMQ(std::vector<uint64_t> numbers);


	/**
	* Deconstructor for the NaiveRMQ class.
	* Needed because the class allocates heap space.
	*/
	~NaiveRMQ();

};