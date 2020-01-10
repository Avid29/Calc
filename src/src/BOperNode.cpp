#include <memory>

#include "../include/BOperNode.h"
#include "../include/ExpNode.h"
#include "../include/FValueNode.h"
#include "../include/OperNode.h"

using namespace std;

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
void BOperNode::AddChild(::ExpNode *node) {
	if (left_child == nullptr) {
		// Add 1st child
		left_child = node;
	} else if (right_child == nullptr) {
		// Add 2nd child
		right_child = node;
	} else { 
		// No more children
		throw;
	}
	node->SetParent(this);
}

/// <summary>
/// Inserts child between this and its last child
/// </summary>
/// <param name="node">this's new child node</param>
void BOperNode:: InsertChild(OperNode* node) {
	ExpNode* grand_child;
	if (right_child == nullptr) {
		grand_child = left_child;
		left_child = nullptr;
	}
	else {
		grand_child = right_child;
		right_child = nullptr;
	}

	// Set node as parent of grand_child and add node as child
	grand_child->InsertAbove(node);
	AddChild(node);
}

/// <summary>
/// Replaces a child with a different ExpNode
/// </summary>
void BOperNode::ReplaceChild(ExpNode* newNode, ExpNode* oldNode) {
	if (left_child == oldNode) {
		// Sets left child to new node and this as newNode's parent
		left_child = newNode;
		newNode->SetParent(this);
		return;
	}
	else if (right_child == oldNode) {
		// Sets right child to new node and this as newNode's parent
		right_child = newNode;
		newNode->SetParent(this);
		return;
	}

	// Didn't find oldNode in children
	// TODO: Something...
}

/// <summary>
/// Simplifies ExpNode and children
/// </summary>
/// <returns>The new simplest node possible in place of this</returns>
ExpNode* BOperNode::Simplify() {

	// Always returns a clone or replacement
	BOperNode *newNode = new BOperNode(oper_);

	ExpNode *simpleLeft = left_child->Simplify();
	ExpNode *simpleRight = right_child->Simplify();

	if (simpleLeft->IsNumericalValue() && simpleRight->IsNumericalValue()) {
		switch (oper_)
		{
			case Operator::POWER:
				return new FValueNode(pow(simpleLeft->AsDouble(), simpleRight->AsDouble()));
		}
	}

	newNode->AddChild(simpleLeft);
	newNode->AddChild(simpleRight);

	return newNode;
}


/// <summary>
/// Gets the expression tree printed from this down
/// </summary>
/// <returns>The expression tree as a string</returns>
string BOperNode::Print() {
	string cache_ = "";
	cache_ += left_child->Print();

	switch (oper_) {
		case Operator::POWER:
			cache_ += "^";
			break;
	}

	cache_ += right_child->Print();
	return cache_;
}
