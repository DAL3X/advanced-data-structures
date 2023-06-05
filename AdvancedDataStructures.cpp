#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include "YTrie.h"


int main() {

    std::vector<int64_t> vect{1, 2, 3, 6, 7, 9, 11, 12, 14, 19};
    YTrie trie = YTrie(vect);
    trie.getPredecessor(15);
    std::cout << trie.getTestTrie()->find("00110")->second->getValue() << "\n";
    std::cout << trie.getTestTrie()->find("01100")->second->getValue() << "\n";
    std::cout << trie.getTestTrie()->find("10011")->second->getValue() << "\n";
}