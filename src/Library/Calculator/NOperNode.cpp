#include <algorithm>
#include <memory>
#include <vector>

#include "AdditiveTerm.h"
#include "ExpNode.h"
#include "FValueNode.h"
#include "IValueNode.h"
#include "MultiplicativeTerm.h"
#include "NOperNode.h"
#include "OperNode.h"
#include "UOperNode.h"

using namespace std;

#pragma region Constrcutors

/// <summary>
/// Copy constructor
/// </summary>
NOperNode::NOperNode(const NOperNode &other) {
	oper_ = other.oper_;
	for (const unique_ptr<ExpNode> &child : other.children_)
	{
		AddChild(child->Clone());
	}
}

/// <summary>
/// Creates an NOperNode based on the operator's character
/// </summary>
/// <param name="node">Character operator</param>
NOperNode::NOperNode(char c) {
	switch (c) {
		case '+':
		case '-':
			oper_ = Operator::ADDITION;
			break;
		case '*':
		case '/':
			oper_ = Operator::MULTIPLICATION;
			break;
		case '=':
			oper_ = Operator::EQUALS;
			break;
	}
}

/// <summary>
/// Creates an NOperNode by operator
/// </summary>
/// <param name="oper">operator</param>
NOperNode::NOperNode(Operator oper) {
	oper_ = oper;
}

#pragma endregion

#pragma region TreeBuilding

/// <summary>
/// Adds child and set its parent
/// </summary>
/// <param name="node">New child node</param>
void NOperNode::AddChild(unique_ptr<ExpNode> node) {
	node->SetParent(this);
	children_.push_back(move(node));
}

/// <summary>
/// Inserts child between this and its last child
/// </summary>
/// <param name="node">this's new child node</param>
void NOperNode::InsertChild(unique_ptr<BranchNode> node) {
	// Gets this's last child and remove from children_
	node->AddChild(move(children_.back()));
	children_.pop_back();
	AddChild(move(node));
}

/// <summary>
/// Inserts child as a child at index
/// </summary>
void NOperNode::AddChildAt(unique_ptr<ExpNode> node, int index) {
	children_.insert(children_.begin() + index, move(node));
}

/// <summary>
/// Steals children from node
/// </summary>
/// <returns>coefficient</returns>
double NOperNode::InheritChildren(NOperNode *node) {
	// Running total of value node children
	double valueProg = 0;
	if (oper_ == Operator::MULTIPLICATION) {
		valueProg = 1;
	}
	
	for (auto &child : node->children_) {
		if (child->IsNumericalValue()) {
			switch (oper_)
			{
				case Operator::ADDITION:
					valueProg += child->AsDouble();
					break;
				case Operator::MULTIPLICATION:
					valueProg *= child->AsDouble();
					break;
			}
		}
		else {
			AddChild(move(child));
		}
	}
	return valueProg;
}

#pragma endregion

/// <summary>
/// Gets child at index
/// </summary>
/// <returns>child at index</returns>
const ExpNode &NOperNode::GetChild(int index) const {
	return *children_[index];
}

/// <summary>
/// Gets amount of children
/// </summary>
/// <returns>children count</returns>
int NOperNode::ChildCount() const {
	return (int)children_.size();
}

void NOperNode::ClearChildren() {
	children_.clear();
}

bool NOperNode::IsConstant() const {
	for (auto& child : children_)
	{
		if (!child->IsConstant()) {
			return false;
		}
	}
	return true;
}

bool NOperNode::IsConstantBy(const VarValueNode& node) const {
	for (auto& child : children_)
	{
		if (!child->IsConstantBy(node)) {
			return false;
		}
	}
	return true;
}

#pragma region Simplify

/// <summary>
/// Simplifies ExpNode and children
/// </summary>
/// <returns>The new simplest node possible in place of this</returns>
unique_ptr<ExpNode> NOperNode::Execute(IOperation* operation) const {
	return operation->Execute(*this);
}

/// <summary>
/// Check if node can inhert node from children and insert if possible
/// </summary>
/// <returns>-1 for failure</returns>
double NOperNode::TryInheritChildren(ExpNode *node) {
	NOperNode *nOperNode = dynamic_cast<NOperNode *>(node);
	if (nOperNode != nullptr && nOperNode->GetOperator() == GetOperator()) {
		// newNode is a duplicate operator
		// inherit children
		// Returns values
		return InheritChildren(nOperNode);
	}
	return -1;
}

#pragma endregion

/// <summary>
/// Gets the expression tree printed from this down
/// </summary>
/// <returns>The expression tree as a string</returns>
string NOperNode::Print(const IPrinter& printer) const {
	return printer.Print(*this);
}

/// <summary>
/// Gets a clone of this
/// </summary>
unique_ptr<ExpNode> NOperNode::Clone() const {
	return make_unique<NOperNode>(*this);
}