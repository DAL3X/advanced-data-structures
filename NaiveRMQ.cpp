#include "NaiveRMQ.h"

int64_t NaiveRMQ::rangeMinimumQuery(int64_t min, int64_t max) {
	return (*savedAnswers)[min * size + max];
}

NaiveRMQ::NaiveRMQ(std::vector<int64_t> numbers) {
	size = numbers.size();
	savedAnswers = new std::vector<int64_t>(size*size);
	for (int64_t i = 0; i < size; i++) {
		int64_t min = i;
		for (int64_t j = i+1; j < size; j++) {
			if (numbers[j] < numbers[min]) {
				min = j;
			}
			(*savedAnswers)[i * size + j] = min;
		}
	}
}

NaiveRMQ::~NaiveRMQ() {
	delete(savedAnswers);
}