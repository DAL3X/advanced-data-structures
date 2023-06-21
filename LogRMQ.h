#pragma once
#include <cstdint>
#include <vector>
#include <unordered_map>

class LogRMQ {

private:

	/** 
	* A vector storing maps, storing pairs of the min value and their position for queries. Has to save both for construction via dynamic programming.
	* The vector dimension marks the beginning value and the map dimension is contains all calulated pairs with the end value as the key.
	* This means getting the minimal value between [x_1,x_2] can be achieved by using savedAnswers->at(x_1)->find(x_2).
	*/
	std::vector<std::unordered_map<int64_t, std::pair<int64_t, int64_t>>*>* savedAnswers;

public:

	int64_t rangeMinimumQuery(int64_t min, int64_t max);

	LogRMQ(std::vector<int64_t> numbers);

	~LogRMQ();
};