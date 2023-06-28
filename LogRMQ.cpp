#include "LogRMQ.h"
#include <cmath>


/**
* Calculates l, which determines how many elements the longest vector in the solution vectors has.
* 
* @param length The length of the input vector.
*/
uint64_t calculateLayers(uint64_t length) {
	return ((uint64_t)std::floor(std::log2(length))) + 1;
}

std::pair<uint64_t, uint64_t> LogRMQ::accessLayerData(uint64_t min, uint64_t max) {
	return savedAnswers->at(min)->at((uint64_t)std::log2(max - min + 1));
}

uint64_t LogRMQ::rangeMinimumQuery(uint64_t min, uint64_t max) {
	// All three query formulas as defined in the lecture.
	uint64_t l = (uint64_t)std::floor(std::log2(max - min + 1));
	uint64_t splitMax = (uint64_t)(min + pow(2, l) - 1);
	uint64_t splitMin = (uint64_t)(max - pow(2, l) + 1);
	std::pair<uint64_t, uint64_t> p1 = accessLayerData(min, splitMax);
	std::pair<uint64_t, uint64_t> p2 = accessLayerData(splitMin, max);
	if (p1.first <= p2.first) {
		return p1.second; 
	}
	else {
		return p2.second;
	}
}


LogRMQ::LogRMQ(std::vector<uint64_t> numbers) {
	savedAnswers = new std::vector<std::vector<std::pair<uint64_t, uint64_t>>*>();
	uint64_t layer = calculateLayers(numbers.size());
	// Initialize and fill in the first (trivial) values.
	for (uint64_t i = 0; i < numbers.size(); i++) {
		savedAnswers->push_back(new std::vector<std::pair<uint64_t, uint64_t>>());
		savedAnswers->at(i)->push_back({numbers[i], i});
	}
	// Now fill in the rest. l and x are defined as in the lecture. We start with l = 1 because we already filled the trivial values.
	for (uint64_t l = 1; l <= layer; l++) {
		for (uint64_t x = 0; x < numbers.size(); x++) {
			uint64_t upperBound = (uint64_t)(pow(2, l) - 1 + x); // -1 because position x in inclusive.
			if (upperBound < numbers.size()) {
				std::pair<uint64_t, uint64_t> p1 = savedAnswers->at(x)->at(l-1);
				std::pair<uint64_t, uint64_t> p2 = savedAnswers->at((uint64_t)(x + pow(2, l-1)))->at(l-1); // Construction formula from the lecture
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
	for (uint64_t i = 0; i < savedAnswers->size(); i++) {
		delete(savedAnswers->at(i));
	}
	delete savedAnswers;
}