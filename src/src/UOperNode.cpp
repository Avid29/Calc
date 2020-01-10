#include <string>
#include <vector>

#include "../include/ExpNode.h"
#include "../include/FValueNode.h"
#include "../include/OperNode.h"
#include "../include/UOperNode.h"

using namespace std;

/// <summary>
/// Creates a UOperNode based on the operator's character
/// </summary>
/// <param name="c">Character operator</param>
UOperNode::UOperNode(char c) : child_ (nullptr) {
	switch (c) {
		case '+':
			oper_ = Operator::POSITIVE;
			break;
		case '-':
			oper_ = Operator::NEGATIVE;
			break;
		case '(':
			oper_ = Operator::UNRESOLVED_PARENTHESIS;
			break;
	}
}

/// <summary>
/// Creates a UOperNode of operator
/// </summary>
/// <param name="oper">operator</param>
UOperNode::UOperNode(Operator oper) : child_ (nullptr) {
	oper_ = oper;
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
/// Replaces a child with a different ExpNode
// </summary>
void UOperNode::ReplaceChild(ExpNode* newNode, ExpNode* oldNode) {
	if (child_ == oldNode) {
		AddChild(newNode, true);
	}
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
	if (oper_ == Operator::UNRESOLVED_PARENTHESIS) {
		oper_ = Operator::PARENTHESIS;
	}
}

/// <summary>
/// Simplifies ExpNode and children
/// </summary>
/// <returns>The new simplest node possible in place of this</returns>
ExpNode* UOperNode::Simplify() {

	// Always returns a clone or replacement
	UOperNode *newNode = new UOperNode(oper_);
	newNode->AddChild(child_->Simplify());
	
	if (newNode->child_->IsNumericalValue()) {
		switch (oper_)
		{
			case Operator::POSITIVE:
			case Operator::PARENTHESIS:
				return new FValueNode(newNode->child_->AsDouble());
			case Operator::NEGATIVE:
				return new FValueNode(-newNode->child_->AsDouble());
		}
	}
	return newNode;
}

/// <summary>
/// Get the expression tree printed from this down
/// </summary>
/// <returns>The expression tree as a string</returns>
string UOperNode::Print() {
	// TODO: Swap to sprintf
	string buffer = "";

	switch (oper_) {
		case Operator::POSITIVE:
			// Consider wheather or not to print unary plus
			buffer.append("+");
			buffer.append(child_->Print());
			break;
		case Operator::NEGATIVE:
			buffer.append("-");
			buffer.append(child_->Print());
			break;
		case Operator::UNRESOLVED_PARENTHESIS:
		case Operator::PARENTHESIS:
			buffer.append("(");
			buffer.append(child_->Print());
			buffer.append(")");
	}
	return buffer;
}
