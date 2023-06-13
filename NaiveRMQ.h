#pragma once
#include <cstdint>
#include <vector>

class NaiveRMQ {

private:
	// Vector used as a 2D vector for saving all answers.
	std::vector<int64_t>* savedAnswers;
	
	// Size of the array that was given to the constructor. Needed for 2D access in the 1D vector.
	int64_t size;

public: 

	/**
	* Performs a range minimum query.
	* Since all answers are already saved, this should take O(1) time.
	* 
	* @param min The minimum range for the query.
	* @param max The maximum range for the query.
	*/
	int64_t rangeMinimumQuery(int64_t min, int64_t max);

	/**
	* Constructor for the NaiveRMQ class.
	* Takes a vector of all numbers and naively generates and saves all answers for all possible range minimum queries on the heap.
	* This takes O(n^2) space, with n being the size of the given array.
	* The answers are saved in a 1D vector, which functions like a 2D vector by splitting it into n blocks of size n. 
	*
	* @param numbers The vector of numbers on which the rmq queries should be possible.
	*/
	NaiveRMQ(std::vector<int64_t> numbers);


	/**
	* Deconstructor for the NaiveRMQ class.
	* Needed because the class allocates heap space.
	*/
	~NaiveRMQ();

};