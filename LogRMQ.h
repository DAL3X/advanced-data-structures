#pragma once
#include <cstdint>
#include <vector>
#include <unordered_map>

class LogRMQ {

private:

	/** 
	* A vector of a vector storing pairs of the min value and their position for queries. Has to save both for construction via dynamic programming.
	* The first dimension represents the beginning value and the second dimension represents layer value l.
	* This means getting the minimal value between [x_1,x_2] can be achieved by using savedAnswers->at(x_1)->at(log_2(x_2 - x_1 + 1)).
	*/
	std::vector<std::vector<std::pair<int64_t, int64_t>>*>* savedAnswers;

	/**
	* Automatically does the transformation of the second dimension to allow for access via borders.
	*/
	std::pair<int64_t, int64_t> accessLayerData(int64_t min, int64_t max);

public:

	int64_t rangeMinimumQuery(int64_t min, int64_t max);

	LogRMQ(std::vector<int64_t> numbers);

	~LogRMQ();
};