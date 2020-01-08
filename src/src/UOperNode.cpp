#include <string>
#include <vector>

#include "../include/ExpNode.h"
#include "../include/OperNode.h"
#include "../include/UOperNode.h"

using namespace std;


/// <summary>
/// Set the child of the node
/// </summary>
void UOperNode::AddChild(::ExpNode *node) {
	if (child_ == nullptr) {
		// Set child
		child_ = node;
	}
	else {
		// No 2nd child
		throw;
	}
	node->SetParent(this);
}


// return expression as a string below this node
string UOperNode::Print() {
	string cache_;
	switch (oper_) {
		case POS:
			cache_ = "+";
			break;
		case NEG:
			cache_ = "-";
			break;
	}
	cache_ += child_->Print();
	return cache_;
}
