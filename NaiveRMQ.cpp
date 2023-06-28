#include "NaiveRMQ.h"

int64_t NaiveRMQ::rangeMinimumQuery(uint64_t min, uint64_t max) {
	return (*savedAnswers)[min * size + max];
}

NaiveRMQ::NaiveRMQ(std::vector<uint64_t> numbers) {
	size = numbers.size();
	savedAnswers = new std::vector<uint64_t>(size*size); // We use the 1D vector as a 2D vector.
	for (uint64_t i = 0; i < size; i++) {
		uint64_t min = i;
		for (uint64_t j = i+1; j < size; j++) {
			if (numbers[j] < numbers[min]) {
				min = j;
			}
			(*savedAnswers)[i * size + j] = min; // i*size+j to get 2D position in 1D array in O(1) runtime
		}
	}
}

NaiveRMQ::~NaiveRMQ() {
	delete(savedAnswers);
}