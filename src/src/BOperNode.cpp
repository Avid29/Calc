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
/// Add node as a child and set node's parent to this
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
		left_child = newNode;
		newNode->SetParent(this);
		return;
	}
	else if (right_child == oldNode) {
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
	left_child = left_child->Simplify();
	right_child = right_child->Simplify();
	double leftDouble = left_child->AsDouble();
	double rightDouble = right_child->AsDouble();
	if (leftDouble != NAN && rightDouble != NAN) {
		switch (oper_)
		{
			case Operator::POWER:
				return new FValueNode(pow(leftDouble, rightDouble));
				break;
		}
	}

	return this;
}


/// <summary>
/// Get the expression tree printed from this down
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
