#pragma once
#include <cstdint>
#include <vector>

class LogRMQ {

private:

	/** 
	* A 2D vector storing a pair of minimum values and the position for queries.Has to save both for construction via dynamic programming.
	* The first dimension is x (beginning value) and the second dimension is l (end value).
	*/
	std::vector<std::vector<std::pair<int64_t, int64_t>>*>* savedAnswers;

public:

	int64_t rangeMinimumQuery(int64_t min, int64_t max);

	LogRMQ(std::vector<int64_t> numbers);

	~LogRMQ();
};