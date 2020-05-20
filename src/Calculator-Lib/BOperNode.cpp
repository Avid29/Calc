#include <memory>
#include <stdexcept>

#include "BOperNode.h"
#include "ExpNode.h"
#include "FValueNode.h"
#include "NOperNode.h"
#include "OperNode.h"

using namespace std;

/// <summary>
/// Copy constructor
/// </summary>
BOperNode::BOperNode(const BOperNode &other) {
	oper_ = other.oper_;
	AddChild(other.left_child->Clone());
	AddChild(other.right_child->Clone());
}

/// <summary>
/// Creates a BOperNode based on the operator's character
/// </summary>
/// <param name="node">Character operator</param>
BOperNode::BOperNode(char c) : left_child (nullptr), right_child (nullptr) {
	switch (c) {
		case '^':
			oper_ = Operator::POWER;
			break;
	}
}

/// <summary>
/// Creates a BOperNode of operator
/// </summary>
/// <param name="oper">operator</param>
BOperNode::BOperNode(Operator oper) : left_child(nullptr), right_child(nullptr) {
	oper_ = oper;
}

/// <summary>
/// Adds node as a child and set node's parent to this
/// </summary>
/// <param name="node">New child node</param>
void BOperNode::AddChild(unique_ptr<ExpNode> node) {
	node->SetParent(this);
	if (left_child == nullptr) {
		// Add 1st child
		left_child = move(node);
	} else if (right_child == nullptr) {
		// Add 2nd child
		right_child = move(node);
	} else { 
		// No more children
		throw;
	}
}

/// <summary>
/// Inserts child between this and its last child
/// </summary>
/// <param name="node">this's new child node</param>
void BOperNode:: InsertChild(unique_ptr<OperNode> node) {
	unique_ptr<ExpNode> newGrandChild;
	if (right_child != nullptr) {
		newGrandChild = move(right_child);
	}
	else {
		newGrandChild = move(left_child);
	}

	// Set node as parent of grand_child and add node as child
	node->AddChild(move(newGrandChild));
	AddChild(move(node));
}

/// <summary>
/// Gets child at index
/// </summary>
/// <returns>child at index</returns>
const ExpNode &BOperNode::GetChild(int index) const {
	if (index == 0) {
		return *left_child;
	}
	else if (index == 1) {
		return *right_child;
	}
	else {
		throw out_of_range("Only 2 children on binary node. 1 is largest index");
	}
}

/// <summary>
/// Gets amount of children
/// </summary>
/// <returns>children count</returns>
int BOperNode::ChildCount() const {
	if (left_child == nullptr)
		return 0;
	else if (right_child == nullptr)
		return 1;
	else
		return 2;
}

/// <summary>
/// Simplifies ExpNode and children
/// </summary>
/// <returns>The new simplest node possible in place of this</returns>
unique_ptr<ExpNode> BOperNode::Simplify() const {

	// Always returns a clone or replacement
	unique_ptr<BOperNode> newNode = make_unique<BOperNode>(oper_);

	unique_ptr<ExpNode> simpleLeft = left_child->Simplify();
	unique_ptr<ExpNode> simpleRight = right_child->Simplify();

	// Returns 1 because anything to the power of 0 is 1
	if (oper_ == Operator::POWER && simpleRight->AsDouble() == 0) {
		return MakeValueNode(1);
	}

	if (simpleLeft->IsNumericalValue() && simpleRight->IsNumericalValue()) {
		switch (oper_)
		{
			case Operator::POWER:
				// Get a ValueNode for left to the power of right
				return MakeValueNode(pow(simpleLeft->AsDouble(), simpleRight->AsDouble()));
		}
	}

	if (oper_ == Operator::POWER &&
		simpleRight->IsNumericalValue() &&
		simpleRight->AsDouble() == floor(simpleRight->AsDouble())) {
		// if oper is Power and if right child is an int 
		// Expand to multiply n times
		unique_ptr<NOperNode> nOperNode = make_unique<NOperNode>('*');
		for (int i = 0; i < simpleRight->AsDouble(); i++) {
			nOperNode->AddChild(simpleLeft->Clone());
		}
		return nOperNode->Simplify();
	}

	newNode->AddChild(move(simpleLeft));
	newNode->AddChild(move(simpleRight));

	return newNode;
}


/// <summary>
/// Gets the expression tree printed from this down
/// </summary>
/// <returns>The expression tree as a string</returns>
string BOperNode::Print(const IPrinter& printer) const {
	return printer.Print(*this);
}

/// <summary>
/// Gets a clone of this
/// </summary>
unique_ptr<ExpNode> BOperNode::Clone() const {
	return make_unique<BOperNode>(*this);
}