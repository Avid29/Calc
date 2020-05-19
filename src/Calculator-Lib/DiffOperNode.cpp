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

void DiffOperNode::AddChild(unique_ptr<ExpNode> node) {
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

void DiffOperNode::InsertChild(unique_ptr<OperNode> node) {
	if (child_ != nullptr) {
		node->AddChild(move(child_));
	}
	AddChild(move(node), true);
}

unique_ptr<ExpNode> DiffOperNode::Simplify() const {
	return make_unique<DiffOperNode>(*this);
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

string DiffOperNode::Print() const {
	string buffer = "";
	buffer.append("\\diff[");
	buffer.append(variable_->Print());
	buffer.append("]{");
	buffer.append(child_->Print());
	buffer.append("}");
	return buffer;
}

unique_ptr<ExpNode> DiffOperNode::Clone() const {
	return make_unique<DiffOperNode>(*this);
}
