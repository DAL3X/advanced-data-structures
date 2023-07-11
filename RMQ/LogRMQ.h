#pragma once
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <utility>

/**
Class for storing RMQ answers and processing the queries in O(1) with O(n log(n)) space usage.
n is the size of the vector, on which the queries are performed.
*/
class LogRMQ {

private:

	/** 
	* A vector of a vector storing pairs of the min value and their position for queries. Has to save both for construction via dynamic programming.
	* The first dimension represents the beginning value and the second dimension represents layer value l.
	* This means getting the minimal value between [x_1,x_2] can be achieved by using savedAnswers->at(x_1)->at(log_2(x_2 - x_1 + 1)).
	*/
	std::vector<std::vector<std::pair<uint64_t, uint64_t>>*>* savedAnswers;

	/**
	* Automatically does the transformation of the second dimension to allow for access via borders.
	*/
	std::pair<uint64_t, uint64_t> accessLayerData(uint64_t min, uint64_t max);

public:

	uint64_t rangeMinimumQuery(uint64_t min, uint64_t max);

	LogRMQ(std::vector<uint64_t> numbers);

	~LogRMQ();
};