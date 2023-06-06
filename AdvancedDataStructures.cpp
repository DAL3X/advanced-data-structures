#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include "YTrie.h"


int main() {

    std::vector<int64_t> vect{1, 3, 6, 7, 9, 12, 14, 19};
    YTrie trie = YTrie(vect);
    std::cout << trie.getPredecessor(18) << "\n";
}