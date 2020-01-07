#include <vector>

#include "../include/ExpNode.h"
#include "../include/OperNode.h"
#include "../include/ValueNode.h"

using namespace std;

ExpNode::ExpNode() : parent_ (nullptr) { }

ExpNode *ExpNode::AddNode(OperNode *node) {
	if (node->GetPriority() < this->GetPriority()) {
		
		// this is an operator
		((OperNode*)this)->AddChild(node);
	} else if (node->GetPriority() == this->GetPriority()) {
		if (parent_ == nullptr) {
			InsertParent(node);
		}
	    else {
			parent_->InsertChild(node);
		}
		// TODO: Handle same NOper

	} else {
		if (parent_ == nullptr) {
			InsertParent(node);
		} else {
			parent_->AddNode(node);
		}
	}
	return node;
}

ExpNode *ExpNode::AddNode(ValueNode *node) {
	if (node->GetPriority() < this->GetPriority()) {
		// this is an operator
		((OperNode*)this)->AddChild(node);
	} else if (GetPriority() == VALUE) {
		if (parent_ == nullptr) {
			throw;	
		}
		parent_->AddChild(node);
	}	

	return node;
}

void ExpNode::SetParent(OperNode* node) {
	parent_ = node;
}

void ExpNode::InsertParent(OperNode *node) {
	node->AddChild(this);
	SetParent(node);
}

OperNode *ExpNode::GetParent() {
	return parent_;
}

bool ExpNode::IsRoot() {
	return parent_ == nullptr;
}
