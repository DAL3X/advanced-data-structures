#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include "NaiveRMQ.h"


int main() {
    std::vector<int64_t> vect{8, 2, 5, 1, 9, 11, 10, 20, 22, 4};
    NaiveRMQ rmq = NaiveRMQ(vect);
    std::cout << rmq.rangeMinimumQuery(0, 9) << std::endl;
    std::cout << rmq.rangeMinimumQuery(0, 2) << std::endl;
    std::cout << rmq.rangeMinimumQuery(4, 8) << std::endl;
}