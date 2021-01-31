#pragma once

#include <stdexcept>

#include "IntegralOperNode.h"

IntegralOperNode::IntegralOperNode() {
	oper_ = Operator::INTEGRAL;
	is_determinate = false;
}

IntegralOperNode::IntegralOperNode(const IntegralOperNode& other) : IntegralOperNode() {
	AddChild(other.child_->Clone());
	SetVariable(make_unique<VarValueNode>(*other.variable_));
}

void IntegralOperNode::SetVariable(unique_ptr<VarValueNode> variable) {
	variable_ = move(variable);
}

const VarValueNode& IntegralOperNode::GetVariable() const {
	return *variable_;
}

void IntegralOperNode::SetUpperBound(unique_ptr<ExpNode> variable) {
	upper_ = move(variable);
	is_determinate = true;
}

const ExpNode& IntegralOperNode::GetUpperBound() const {
	return *upper_;
}

void IntegralOperNode::SetLowerBound(unique_ptr<ExpNode> variable) {
	lower_ = move(variable);
	is_determinate = true;
}

const ExpNode& IntegralOperNode::GetLowerBound() const {
	return *lower_;
}

void IntegralOperNode::AddChild(unique_ptr<ExpNode> node) {
	AddChild(move(node), false);
}

void IntegralOperNode::AddChild(unique_ptr<ExpNode> node, bool overwrite) {
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

void IntegralOperNode::InsertChild(unique_ptr<BranchNode> node) {
	if (child_ != nullptr) {
		node->AddChild(move(child_));
	}
	AddChild(move(node), true);
}

unique_ptr<ExpNode> IntegralOperNode::Execute(IOperation* operation) const {
	return operation->Execute(*this);
}

const ExpNode& IntegralOperNode::GetChild(int index) const {
	if (index == 0) {
		return *child_;
	}
	else {
		throw out_of_range("Only 1 children on unary node. 0 is only index");
	}
}

int IntegralOperNode::ChildCount() const {
	return child_ != nullptr ? 1 : 0;
}

void IntegralOperNode::ClearChildren() {
	child_ = nullptr;
	variable_ = nullptr;
	upper_ = nullptr;
	lower_ = nullptr;
}

bool IntegralOperNode::IsConstant() const {
	return child_->IsConstant();
}

bool IntegralOperNode::IsConstantBy(const VarValueNode& node) const {
	return child_->IsConstantBy(node);
}

string IntegralOperNode::Print(const IPrinter& printer) const {
	return printer.Print(*this);
}

unique_ptr<ExpNode> IntegralOperNode::Clone() const {
	return make_unique<IntegralOperNode>(*this);
}
