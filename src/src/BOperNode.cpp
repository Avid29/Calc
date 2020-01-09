#include <memory>

#include "../include/BOperNode.h"
#include "../include/ExpNode.h"
#include "../include/OperNode.h"

using namespace std;

/// <summary>
/// Add node as a child and set node's parent to this
/// </summary>
/// <param name="node">New child node</param>
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

/// <summary>
/// Get the expression tree printed from this down
/// </summary>
/// <returns>The expression tree as a string</returns>
string BOperNode::Print() {
	string cache_ = "";
	cache_ += left_child->Print();

	switch (oper_) {
		case Operator::POWER:
			cache_ += "^";
			break;
	}

	cache_ += right_child->Print();
	return cache_;
}
