#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include "YTrie.h"


int main() {

    std::vector<int64_t> vect{1, 2, 3, 6, 7, 9, 11, 12, 14};
    YTrie trie = YTrie(vect);
    std::cout << trie.getTestTrie()->find("3")->second->getValue() << "\n";
    std::cout << trie.getTestTrie()->find("9")->second->getValue() << "\n";
    std::cout << trie.getTestTrie()->find("14")->second->getValue() << "\n";
}