#include <iostream>
#include <cstdint>
#include <vector>
#include "YTrie.h"


int main() {
    std::vector<int64_t> vect{1, 2, 3, 6, 7, 9, 11, 12, 14, 15};
    YTrie trie = YTrie(vect);
    std::cout << trie.getTestRep()[0] << "\n";
    std::cout << trie.getTestTree(15)->getRoot()->getValue() << "\n";
}