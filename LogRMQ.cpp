#include "LogRMQ.h"
#include <cmath>


/**
* Calculates l, which determines how many elements the longest vector in the solution vectors has.
* 
* @param length The length of the input vector.
*/
int64_t calculateLayers(int64_t length) {
	return ((int64_t)std::floor(std::log2(length))) + 1;
}

std::pair<int64_t, int64_t> LogRMQ::accessLayerData(int64_t min, int64_t max) {
	return savedAnswers->at(min)->at(std::log2(max - min + 1));
}

int64_t LogRMQ::rangeMinimumQuery(int64_t min, int64_t max) {
	// All three query formulas as defined in the lecture.
	int64_t l = (int64_t)std::floor(std::log2(max - min - 1));
	int64_t splitMax = min + pow(2, l) - 1;
	int64_t splitMin = max - pow(2, l) + 1;
	std::pair<int64_t, int64_t> p1 = accessLayerData(min, splitMax);
	std::pair<int64_t, int64_t> p2 = accessLayerData(splitMin, max);
	if (p1.first <= p2.first) {
		return p1.second; 
	}
	else {
		return p2.second;
	}
}


LogRMQ::LogRMQ(std::vector<int64_t> numbers) {
	savedAnswers = new std::vector<std::vector<std::pair<int64_t, int64_t>>*>();
	int64_t layer = calculateLayers(numbers.size());
	// Initialize and fill in the first (trivial) values.
	for (int64_t i = 0; i < numbers.size(); i++) {
		savedAnswers->push_back(new std::vector<std::pair<int64_t, int64_t>>());
		savedAnswers->at(i)->push_back({numbers[i], i});
	}
	// Now fill in the rest. l and x are defined as in the lecture. We start with l = 1 because we already filled the trivial values.
	for (int64_t l = 1; l <= layer; l++) {
		for (int64_t x = 0; x < numbers.size(); x++) {
			int64_t upperBound = pow(2, l) - 1 + x; // -1 because position x in inclusive.
			if (upperBound < numbers.size()) {
				std::pair<int64_t, int64_t> p1 = savedAnswers->at(x)->at(l-1);
				std::pair<int64_t, int64_t> p2 = savedAnswers->at(x + pow(2, l-1))->at(l-1); // Construction formula from the lecture
				if (p1.first <= p2.first) { // p1 is smaller or same size
					savedAnswers->at(x)->push_back(p1);
				}
				else { // p2 is smaller 
					savedAnswers->at(x)->push_back(p2);
				}
			}
		}
	}
}


LogRMQ::~LogRMQ() {
	for (int64_t i = 0; i < savedAnswers->size(); i++) {
		delete(savedAnswers->at(i));
	}
	delete savedAnswers;
}