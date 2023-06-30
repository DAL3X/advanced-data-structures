#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include "CartesianRMQ.h"


int main() {
    std::vector<uint64_t> vect;
    for (uint64_t i = 0; i < 5000; i++) {
        vect.push_back(i);
    }
    CartesianRMQ rmq = CartesianRMQ(vect);
    std::cout << rmq.rangeMinimumQuery(0, 2) << std::endl;
}