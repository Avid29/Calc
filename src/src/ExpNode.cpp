#include <vector>

#include "../include/ExpNode.h"
#include "../include/OperNode.h"
#include "../include/ValueNode.h"

using namespace std;

ExpNode::ExpNode() : parent_ (nullptr) { }

// Add an OperNode by priority
ExpNode *ExpNode::AddNode(OperNode *node) {
	if (node->GetPriority() < this->GetPriority()) {
		// this is an operator
		((OperNode*)this)->InsertChild(node);
	} else if (node->GetPriority() == this->GetPriority()) {
		if (parent_ == nullptr) {
			InsertAbove(node);
		}
	    else {
			parent_->InsertChild(node);
		}
		// TODO: Handle same NOper

	} else {
		if (parent_ == nullptr) {
			InsertAbove(node);
		} else {
			parent_->AddNode(node);
		}
	}
	return node;
}

// Try add a ValueNode by priority
ExpNode *ExpNode::AddNode(ValueNode *node) {
	if (node->GetPriority() < this->GetPriority()) {
		// this must be an operator
		((OperNode*)this)->AddChild(node);
	} else if (GetPriority() == VALUE) {
		if (parent_ == nullptr) {
			// Can't add a value node
			throw;	
		}
		parent_->AddChild(node);
	}	

	return node;
}


// Set the parent of the node in the tree
void ExpNode::SetParent(OperNode* node) {
	parent_ = node;
}

// Inserts a node above the this node
void ExpNode::InsertAbove(OperNode *node) {
	node->AddChild(this);
	SetParent(node);
}

// Returns parent_
OperNode *ExpNode::GetParent() {
	return parent_;
}

// Checks if ExpNode has parent
bool ExpNode::IsRoot() {
	return parent_ == nullptr;
}
