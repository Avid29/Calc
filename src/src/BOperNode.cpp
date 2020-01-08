#include <memory>

#include "../include/BOperNode.h"
#include "../include/ExpNode.h"
#include "../include/OperNode.h"

using namespace std;

// Add node as a child and set node's parent to this
void BOperNode::AddChild(::ExpNode *node) {
	if (left_child == nullptr) {
		// Add 1st child
		left_child = node;
	} else if (right_child == nullptr) {
		// Add 2nd child
		right_child = node;
	} else { 
		// No more children
		throw;
	}
	node->SetParent(this);
}

// return expression as a string below this node
string BOperNode::Print() {
	string cache_ = "";
	cache_ += left_child->Print();

	switch (oper_) {
		case POWER:
			cache_ += "^";
			break;
	}

	cache_ += right_child->Print();
	return cache_;
}
