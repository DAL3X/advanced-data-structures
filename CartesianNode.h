#pragma once
#include <cstdint>

/**
* Node for a cartesian tree. It knows up to 2 children, a value and it's parent to allow upwards search in the tree.
*/
class CartesianNode {

private:
	// The value this node holds.
	std::uint64_t value_;

	// The left child.
	CartesianNode* left_ = nullptr;

	// The right child.
	CartesianNode* right_ = nullptr;

	// The right child.
	CartesianNode* parent_ = nullptr;

public:

	// Getter for children, parents and value.
	CartesianNode* getLeftChild();
	CartesianNode* getRightChild();
	CartesianNode* getParent();
	uint64_t getValue();

	// Setter for children and parent.
	void setLeftChild(CartesianNode* node);
	void setRightChild(CartesianNode* node);
	void setParent(CartesianNode* node);

	CartesianNode(uint64_t value, CartesianNode* parent, CartesianNode* left, CartesianNode* right);
	CartesianNode(uint64_t value, CartesianNode* parent);

	/**
	* Cleans up the lower nodes to avoid memory leaks.
	*/
	~CartesianNode();
};