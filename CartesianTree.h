#pragma once
#include "CartesianNode.h"

/**
* Class representing a cartesian tree. It only consists of a root. The rest of the tree exists implicitly through the children of the root.
*/
class CartesianTree {

private:
	CartesianNode* root_ = nullptr;

public:
	// Constructor, getter and setter to manipulate the root.
	CartesianTree(CartesianNode* root);
	CartesianNode* getRoot();
	void setRoot(CartesianNode* node);
};