#include <memory>
#include <vector>

#include "../include/ExpNode.h"
#include "../include/NOperNode.h"
#include "../include/OperNode.h"

using namespace std;

/// <summary>
/// Create an NOperNode based on the operator's character
/// </summary>
/// <param name="node">Character operator</param>
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

/// <summary>
/// Add child and set its parent
/// </summary>
/// <param name="node">New child node</param>
void NOperNode::AddChild(::ExpNode *node) {
	children_.push_back(node);
	node->SetParent(this);
}

/// <summary>
/// Insert child between this and its last child
/// </summary>
/// <param name="node">this's new child node</param>
void NOperNode::InsertChild(::OperNode *node) {	
	// Get this's last child and remove from children_
	ExpNode *grand_child = children_.back();
	children_.pop_back();

	// Set node as parent of grand_child and add node as child
	grand_child->InsertAbove(node);
	AddChild(node);
}

/// <summary>
/// Get the expression tree printed from this down
/// </summary>
/// <returns>The expression tree as a string</returns>
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
