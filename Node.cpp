#include "Node.h"

class Node {

private:
	std::int64_t value_ = 0;
	std::unique_ptr<Node> left_ = nullptr;
	std::unique_ptr<Node> right_ = nullptr;

public:
	Node& getLeftChild() {
		return *(left_.get());
	}
	Node& getRightChild() {
		return *(right_.get());
	}
	int64_t getValue() {
		return value_;
	}

	Node(int64_t value, Node& left, Node& right):
		value_(value),
		left_(std::make_unique<Node>(left)),
		right_(std::make_unique<Node>(right)) {}

	Node(int64_t value, Node& left):
		value_(value),
		left_(std::make_unique<Node>(left)) {}

	Node(int64_t value, Node& right):
		value_(value),
		right_(std::make_unique<Node>(right)) {}

	// Leaf
	Node(int64_t value) :
		value_(value) {}
};
