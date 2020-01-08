#include <memory>
#include <vector>

#include "../include/ExpNode.h"
#include "../include/NOperNode.h"
#include "../include/OperNode.h"

using namespace std;

// Create NOperNode based on oper character
NOperNode::NOperNode(char c) {
	switch (c) {
		case '+':
			oper_ = ADDITION;
			break;
		case '*':
			oper_ = MULTIPLICATION;
			break;
	}
}

// Add a child and set its parent
void NOperNode::AddChild(::ExpNode *node) {
	children_.push_back(node);
	node->SetParent(this);
}

// Add a child between another node
void NOperNode::InsertChild(::OperNode *node) {	
	// get node's new child and remove from this
	ExpNode *grand_child = children_.back();
	children_.pop_back();

	// Set node as parent of grand_child and add node as child
	grand_child->InsertAbove(node);
	AddChild(node);
}

// return expression as a string below this node
string NOperNode::Print() {
	string cache_;
	for (int i = 0; i < children_.size(); i++) {
		if (i != 0) {
			switch (oper_) {
				case ADDITION:
					cache_ += "+";
					break;
				case MULTIPLICATION:
					cache_ += "*";
					break;
			}
		}
		ExpNode *node = children_[i];
		cache_ += node->Print();	
	}
	return cache_;
}
