#include <memory>
#include <vector>

#include "../include/ExpNode.h"
#include "../include/FValueNode.h"
#include "../include/NOperNode.h"
#include "../include/OperNode.h"

using namespace std;

/// <summary>
/// Creates an NOperNode based on the operator's character
/// </summary>
/// <param name="node">Character operator</param>
NOperNode::NOperNode(char c) {
	switch (c) {
		case '+':
			oper_ = Operator::ADDITION;
			break;
		case '*':
			oper_ = Operator::MULTIPLICATION;
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

/// <summary>
/// Adds child and set its parent
/// </summary>
/// <param name="node">New child node</param>
void NOperNode::AddChild(::ExpNode *node) {
	children_.push_back(node);
	node->SetParent(this);
}

/// <summary>
/// Inserts child between this and its last child
/// </summary>
/// <param name="node">this's new child node</param>
void NOperNode::InsertChild(::OperNode *node) {	
	// Gets this's last child and remove from children_
	ExpNode *grand_child = children_.back();
	children_.pop_back();

	// Sets node as parent of grand_child and add node as child
	grand_child->InsertAbove(node);
	AddChild(node);
}

/// <summary>
/// Replaces a child with a different ExpNode
/// </summary>
void NOperNode::ReplaceChild(ExpNode* newNode, ExpNode* oldNode) {
	for (int i = 0; i < children_.size(); i++) {
		if (children_[i] == oldNode) {
			children_[i] = newNode;
			newNode->SetParent(this);
			return;
		}
	}
	// Didn't find oldNode in children_
	// TODO: Something...
}

/// <summary>
/// Simplifies ExpNode and children
/// </summary>
/// <returns>The new simplest node possible in place of this</returns>
ExpNode *NOperNode::Simplify() {
	// Running total of value node children
	double valueProg = 0;
	if (oper_ == Operator::MULTIPLICATION) {
		valueProg = 1;
	}

	// Always returns a clone or replacement
	NOperNode *newNode = new NOperNode(oper_);

	// Iterates whole vector
	auto i = std::begin(children_);
	while (i != std::end(children_)) {
		ExpNode *node = *i;
		// Doesn't update node in children_
		node = node->Simplify();

		if (node->IsNumericalValue()) {
			// Add node value to total value progress
			switch (oper_)
			{
				case Operator::ADDITION:
					valueProg += node->AsDouble();
					break;
				case Operator::MULTIPLICATION:
					valueProg *= node->AsDouble();
					break;
			}
		}
		else {
			newNode->AddChild(node);
		}

		++i;
	}

	newNode->AddChild(new FValueNode(valueProg));

	// TODO: Sort children by degree

	if (newNode->children_.size() == 1) {
		return newNode->children_[0];
	}

	return newNode;
}

/// <summary>
/// Gets the expression tree printed from this down
/// </summary>
/// <returns>The expression tree as a string</returns>
string NOperNode::Print() {
	string cache_;
	for (int i = 0; i < children_.size(); i++) {
		if (i != 0) {
			switch (oper_) {
				case Operator::ADDITION:
					cache_ += "+";
					break;
				case Operator::MULTIPLICATION:
					cache_ += "*";
					break;
			}
		}
		ExpNode *node = children_[i];
		cache_ += node->Print();	
	}
	return cache_;
}
