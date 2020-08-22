#pragma once

#include <stdexcept>

#include "DiffOperNode.h"

using namespace std;

DiffOperNode::DiffOperNode() {
	oper_ = Operator::DERIVATIVE;
}

DiffOperNode::DiffOperNode(const DiffOperNode& other) : DiffOperNode() {
	AddChild(other.child_->Clone());
	SetVariable(make_unique<VarValueNode>(*other.variable_));
}

void DiffOperNode::SetVariable(unique_ptr<VarValueNode> variable) {
	variable_ = move(variable);
}

const VarValueNode& DiffOperNode::GetVariable() const {
	return *variable_;
}

void DiffOperNode::AddChild(unique_ptr<ExpNode> node) {
	AddChild(move(node), false);
}

void DiffOperNode::AddChild(unique_ptr<ExpNode> node, bool overwrite) {
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

void DiffOperNode::InsertChild(unique_ptr<BranchNode> node) {
	if (child_ != nullptr) {
		node->AddChild(move(child_));
	}
	AddChild(move(node), true);
}

unique_ptr<ExpNode> DiffOperNode::Execute(IOperation* operation) const {
	return operation->Execute(*this);
}

const ExpNode& DiffOperNode::GetChild(int index) const {
	if (index == 0) {
		return *child_;
	}
	else {
		throw out_of_range("Only 1 children on unary node. 0 is only index");
	}
}


int DiffOperNode::ChildCount() const {
	return child_ != nullptr ? 1 : 0;
}

void DiffOperNode::ClearChildren() {
	child_ = nullptr;
	variable_ = nullptr;
}

bool DiffOperNode::IsConstant() const {
	return child_->IsConstant();
}

bool DiffOperNode::IsConstantBy(const VarValueNode& node) const {
	return child_->IsConstantBy(node);
}

string DiffOperNode::Print(const IPrinter& printer) const {
	return printer.Print(*this);
}

unique_ptr<ExpNode> DiffOperNode::Clone() const {
	return make_unique<DiffOperNode>(*this);
}
