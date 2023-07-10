#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include "RMQ/CartesianRMQ.h"
#include "Predecessor/YTrie.h"

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

int main(int argc, const char** argv) {

	std::string selection = std::string(argv[0]);
	std::string inputFile = std::string(argv[1]);
	std::string outputFile = std::string(argv[2]);

	if (selection == "pd") {
		std::vector<uint64_t>* values = new std::vector<uint64_t>();
		std::vector<uint64_t>* queries = new std::vector<uint64_t>();
		readInPredecessorFile(inputFile, values, queries);
		int i = 0;
	}
	else if (selection == "rmq") {
		std::vector<uint64_t>* values = new std::vector<uint64_t>();
		std::vector<std::pair<uint64_t, uint64_t>>* queries = new std::vector<std::pair<uint64_t, uint64_t>>();
		readInRMQFile(inputFile, values, queries);
		int i = 0;
	}
	return 0;
}