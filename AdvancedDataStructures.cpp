#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <chrono>
#include "RMQ/CartesianRMQ.h"
#include "Predecessor/YTrie.h"
#include "malloc_count/malloc_count.h" // Use of external library was allowed via mail on the 3. of june.

void readInPredecessorFile(std::string path, std::vector<uint64_t>* values, std::vector<uint64_t>* queries) {
	std::ifstream file(path);
	uint64_t length, readValue;
	file >> length;
	// Read in all the values on which the data structure is built,
	for (uint64_t i = 0; i < length; i++) {
		file >> readValue;
		values->push_back(readValue);
	}
	// Read in all the queries.
	while (file >> readValue) {
		queries->push_back(readValue);
	}
}

void readInRMQFile(std::string path, std::vector<uint64_t>* values, std::vector<std::pair<uint64_t, uint64_t>>* queries) {
	std::ifstream file(path);
	uint64_t length, readValue;
	std::pair<uint64_t, uint64_t> readPair;
	file >> length;
	// Read in all the values on which the data structure is built,
	for (uint64_t i = 0; i < length; i++) {
		file >> readValue;
		values->push_back(readValue);
	}
	// Read in all the queries.
	std::string line;
	while (file >> line ) {
		size_t splitpoint = line.find(",");
		std::string tokenOne = line.substr(0, splitpoint);
		std::string tokenTwo = line.substr(splitpoint + 1, line.length());
		queries->push_back({ std::stoull(tokenOne), std::stoull(tokenTwo) });
	}
}

void writeAnswerFile(std::string path, std::vector<uint64_t>* answers) {
	std::ofstream file(path);
	for (uint64_t i = 0; i < answers->size(); i++) {
		file << answers->at(i) << std::endl;
	}
	file.close();
}

int main(int argc, const char** argv) {
	std::string selection = std::string(argv[1]);
	std::string inputFile = std::string(argv[2]);
	std::string outputFile = std::string(argv[3]);
	std::chrono::milliseconds duration;
	uint memory;
	std::vector<uint64_t> values;
	std::vector<uint64_t> *answers = new std::vector<uint64_t>();
	if (selection == "pd") {
		std::vector<uint64_t> queries;
		readInPredecessorFile(inputFile, &values, &queries);
		auto startTiming = std::chrono::high_resolution_clock::now();
		// Now build the datastructure and answer all queries.
		YTrie *predecessor = new YTrie(values);
		for (uint64_t i = 0; i < queries.size(); i++) {
			answers->push_back(predecessor->getPredecessor(queries[i]));
		}
		auto endTiming = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTiming- startTiming);
		memory = malloc_count_current();
	}
	else if (selection == "rmq") {
		std::vector<std::pair<uint64_t, uint64_t>> queries;
		readInRMQFile(inputFile, &values, &queries);
		auto startTiming = std::chrono::high_resolution_clock::now();
		// Now build the datastructure and answer all queries.
		CartesianRMQ *rmq = new CartesianRMQ(values);
		for (uint64_t i = 0; i < queries.size(); i++) {
			answers->push_back(rmq->rangeMinimumQuery(queries[i].first, queries[i].second));
		}
		auto endTiming = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTiming- startTiming);
		memory = malloc_count_current();
	}
	else {
		return 1;
	}
	memory = memory * 8; // Cast from bytes to bits
	writeAnswerFile(outputFile, answers);
	std::cout << "RESULT " << "algo=" << selection << " name=simon_bothe" << " time=" << duration.count() << " space=" << memory << std::endl;
	return 0;
}