#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include "CartesianRMQ.h"


int main() {
    std::vector<uint64_t> vect = {8,2,5,1,9,11,10,20,22,4};
    for (uint64_t i = 30; i < 5000; i++) {
        vect.push_back(i);
    }
    CartesianRMQ rmq = CartesianRMQ(vect);
    std::cout << rmq.rangeMinimumQuery(0, 9) << std::endl;
    std::cout << rmq.rangeMinimumQuery(0, 2) << std::endl;
    std::cout << rmq.rangeMinimumQuery(4, 8) << std::endl;
    std::cout << rmq.rangeMinimumQuery(7, 60) << std::endl;
}