#include <string>
#include <vector>

#include "../include/ExpNode.h"
#include "../include/OperNode.h"
#include "../include/UOperNode.h"

using namespace std;
/// <summary>
/// Create a UOperNode based on the operator's character
/// </summary>
/// <param name="node">Character operator</param>
UOperNode::UOperNode(char c) {
	switch (c) {
		case '+':
			oper_ = Operator::POSITIVE_OPER;
			break;
		case '-':
			oper_ = Operator::NEGATIVE_OPER;
			break;
		case '(':
			oper_ = Operator::OVERRIDE_OPER;
			break;
	}
}

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

/// <summary>
/// Set the child of the node
/// </summary>
void UOperNode::AddChild(::ExpNode *node, bool overwrite) {
	if (child_ == nullptr || overwrite) {
		// Set child
		child_ = node;
	}
	else {
		// No 2nd child
		throw;
	}
	node->SetParent(this);
}

/// <summary>
/// Insert child between this and its child
/// </summary>
/// <param name="node">this's new child node</param>
void UOperNode::InsertChild(::OperNode *node) {
	ExpNode* grand_child = child_;
	grand_child->InsertAbove(node);
	AddChild(node, true);
}

/// <summary>
/// Check if UOperNode's child_ is set
/// </summary>
/// <returns>true if child_ is not null</returns>
bool UOperNode::HasChild() {
	return child_ != nullptr;
}

/// <summary>
/// Changes priority from OVERRIDE to OVERRIDEN when OVERRIDE finished
/// </summary>
void UOperNode::RemoveOverride() {
	if (oper_ == OVERRIDE_OPER) {
		oper_ = OVERRIDEN_OPER;
	}
}

/// <summary>
/// Get the expression tree printed from this down
/// </summary>
/// <returns>The expression tree as a string</returns>
string UOperNode::Print() {
	// TODO: Swap to sprintf
	string buffer = "";

	switch (oper_) {
		case POSITIVE_OPER:
			buffer.append("+");
			buffer.append(child_->Print());
			break;
		case NEGATIVE_OPER:
			buffer.append("-");
			buffer.append(child_->Print());
			break;
		case OVERRIDE_OPER:
		case OVERRIDEN_OPER:
			buffer.append("(");
			buffer.append(child_->Print());
			buffer.append(")");
	}
	return buffer;
}
