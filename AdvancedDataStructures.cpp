#include <iostream>
#include <cstdint>
#include <vector>
#include "BST.h"

int main() {
    std::vector<int64_t> vect{10, 20, 30 , 40, 50, 60, 70};
    BST tree = BST(vect);
    std::cout << tree.getPredecessor(0, 51) << "\n";
}