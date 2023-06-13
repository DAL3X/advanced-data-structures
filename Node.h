#pragma once
#include <cstdint>

/**
* Node for a binary search tree. It knows up to 2 children and holds a value.
*/
class Node {

private:
	// The value this node holds.
	std::int64_t value_ = 0;

	// The left child.
	Node* left_ = nullptr;

	// The right child.
	Node* right_ = nullptr;

public:
	/**
	* Returns the left child.
	* If no child is found, it returns nullptr.
	* 
	* @return left child or nullptr, if not present.
	*/
	Node* getLeftChild();

	/**
	* Returns the right child.
	* If no child is found, it returns nullptr.
	*
	* @return right child or nullptr, if not present.
	*/
	Node* getRightChild();

	/**
	* Returns the value that this node holds.
	* 
	* @return the value for this node.
	*/
	int64_t getValue();

	Node(int64_t value, Node* leftNode, Node* rightNode);

	/**
	* Cleans up the lower nodes to avoid memory leaks.
	*/ 
	~Node();
};