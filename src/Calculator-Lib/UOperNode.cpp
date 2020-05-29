#include <stdexcept>
#include <string>
#include <vector>
#include <math.h>

#include "ExpNode.h"
#include "FValueNode.h"
#include "OperNode.h"
#include "UOperNode.h"

using namespace std;

/// <summary>
/// Copy constructor
/// </summary>
UOperNode::UOperNode(const UOperNode &other) {
	oper_ = other.oper_;
	AddChild(other.child_->Clone());
}

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
		case '[':
			oper_ = Operator::UNRESOLVED_PARENTHESIS;
			break;
		case '/':
			oper_ = Operator::RECIPROCAL;
			break;
		case '\'':
			oper_ = Operator::DERIVATIVE;
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
void UOperNode::AddChild(unique_ptr<ExpNode> node) {
	node->SetParent(this);
	if (child_ == nullptr) {
		// Set child
		child_ = move(node);
	}
	else {
		// No 2nd child
		throw;
	}
}

/// <summary>
/// Set the child of the node
/// </summary>
void UOperNode::AddChild(unique_ptr<ExpNode> node, bool overwrite) {
	node->SetParent(this);
	if (child_ == nullptr || overwrite) {
		// Set child
		child_ = move(node);
	}
	else {
		// No 2nd child
		throw;
	}
}

/// <summary>
/// Insert child between this and its child
/// </summary>
/// <param name="node">this's new child node</param>
void UOperNode::InsertChild(unique_ptr<OperNode> node) {
	if (child_ != nullptr) {
		node->AddChild(move(child_));
	}
	AddChild(move(node), true);
}

/// <summary>
/// Gets child at index
/// </summary>
/// <returns>child at index</returns>
const ExpNode &UOperNode::GetChild(int index) const{
	if (index == 0) {
		return *child_;
	}
	else {
		throw out_of_range("Only 1 children on unary node. 0 is only index");
	}
}

/// <summary>
/// Gets amount of children
/// </summary>
/// <returns>children count</returns>
int UOperNode::ChildCount() const {
	return child_ != nullptr ? 1 : 0;
}

void UOperNode::ClearChildren() {
	child_ = nullptr;
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

bool UOperNode::IsConstant() const {
	return child_->IsConstant();
}

bool UOperNode::IsConstantBy(const VarValueNode& node) const {
	return child_->IsConstantBy(node);
}

/// <summary>
/// Simplifies ExpNode and children
/// </summary>
/// <returns>The new simplest node possible in place of this</returns>
unique_ptr<ExpNode> UOperNode::Execute(IOperation* operation) const {
	return operation->Execute(*this);
}

/// <summary>
/// Get the expression tree printed from this down
/// </summary>
/// <returns>The expression tree as a string</returns>
string UOperNode::Print(const IPrinter& printer) const {
	return printer.Print(*this);
}

/// <summary>
/// Gets a clone of this
/// </summary>
unique_ptr<ExpNode> UOperNode::Clone() const {
	return make_unique<UOperNode>(*this);
}

/// <summary>
/// Checks if the operation is a suffix or prefix
/// </summary>
bool IsSuffix(Operator oper) {
	return oper == Operator::DERIVATIVE;
}
