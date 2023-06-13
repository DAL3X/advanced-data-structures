#pragma once
#include <cstdint>
#include <vector>

class NaiveRMQ {

private:
	std::vector<int64_t>* savedAnswers;
	int64_t size;

public: 
	int64_t rangeMinimumQuery(int64_t min, int64_t max);
	NaiveRMQ(std::vector<int64_t> numbers);
	~NaiveRMQ();

};