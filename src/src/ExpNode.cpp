#include <vector>

#include "../include/ExpNode.h"
#include "../include/OperNode.h"
#include "../include/ValueNode.h"

using namespace std;

ExpNode::ExpNode() : parent_ (nullptr) { }

/// <summary>
/// Add an OperNode, in the appropiate place, to the tree
/// </summary>
/// <param name="node">New OperNode for the tree</param>
ExpNode *ExpNode::AddNode(OperNode *node) {
	if (node->GetPriority() < this->GetPriority()) {
		// this is an operator
		((OperNode*)this)->InsertChild(node);
	} else if (node->GetPriority() == this->GetPriority()) {

		// If the same unary operator, combine
		if (((OperNode*)this)->GetOperator() == node->GetOperator() && IsUnary(node->GetOperator())) {
			// TODO: Move add node children to this children
			return this;
		}

		if (parent_ == nullptr) {
			// If the parent of this is null, make this the new root node
			InsertAbove(node);
		}
	    else {
			// Insert the node between this and its parent
			parent_->InsertChild(node);
		}

	} else {
		if (parent_ == nullptr) {
			InsertAbove(node);
		} else {
			return parent_->AddNode(node);
		}
	}
	return node;
}

/// <summary>
/// Add a ValueNode, in the appropiate place, to the tree
/// </summary>
/// <param name="node">New ValueNode for the tree</param>
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

/// <summary>
/// Set <see cref="node"/> as the parent of <see cref="this"/>
/// </summary>
/// <param name="node">New parent node</param>
void ExpNode::SetParent(OperNode* node) {
	parent_ = node;
}

/// <summary>
/// Set node as the parent of this and this as the child of node
/// </summary>
/// <param name="node">New parent node</param>
void ExpNode::InsertAbove(OperNode *node) {
	node->AddChild(this);
	SetParent(node);
}

/// <summary>
/// Get parent_
/// </summary>
/// <returns>parent_</returns>
OperNode *ExpNode::GetParent() {
	return parent_;
}
/// <summary>
/// Checks if this has parent (if it does not, it's the root node
/// </summary>
/// <returns>true if this is the root node</returns>
bool ExpNode::IsRoot() {
	return parent_ == nullptr;
}
