#pragma once
#include "Node.h"
#include <cstdint>
#include <vector>

/**
* Class representing a binary searching tree.
* It consists of a single pointer to a root node, which knows its children.
*/
class BST {

private:
	Node* root_ = nullptr;

public:
	/**
	* Performs the predecessor query.
	* Since this should later be used in a Y-Trie, it also gets the maximum (representant) of the left neighbour tree.
	* This allows it to dynamically find out, if the predecessor is actually the maximum of the neighbour, or present in itself.
	* 
	* @param maxSmallerTree The maximum (representant) of the left neighbour tree in the Y-Trie.
	* @param limit The number, for which we want to find the predecessor.
	*/
	int64_t getPredecessor(int64_t maxSmallerTree, int64_t limit);

	Node* getRoot();

	/**
	* Constructs the binary search tree from the given values.
	* These given values will later be present as the values of the tree nodes.
	* 
	* @params values The vector of numbers, which should be used to construct the binary search tree.
	*/
	BST(std::vector<int64_t> values);

	~BST();
};