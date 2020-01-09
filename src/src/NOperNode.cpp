#include <memory>
#include <vector>

#include "../include/ExpNode.h"
#include "../include/FValueNode.h"
#include "../include/NOperNode.h"
#include "../include/OperNode.h"

using namespace std;

/// <summary>
/// Create an NOperNode based on the operator's character
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
/// Add child and set its parent
/// </summary>
/// <param name="node">New child node</param>
void NOperNode::AddChild(::ExpNode *node) {
	children_.push_back(node);
	node->SetParent(this);
}

/// <summary>
/// Insert child between this and its last child
/// </summary>
/// <param name="node">this's new child node</param>
void NOperNode::InsertChild(::OperNode *node) {	
	// Get this's last child and remove from children_
	ExpNode *grand_child = children_.back();
	children_.pop_back();

	// Set node as parent of grand_child and add node as child
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
ExpNode* NOperNode::Simplify() {
	double sumProg = 0;
	if (oper_ == Operator::MULTIPLICATION) {
		sumProg = 1;
	}

	ExpNode* replace_node = nullptr;

	auto i = std::begin(children_);
	while (i != std::end(children_)) {
		ExpNode* node = &**i;
		double pendingValue = node->Simplify()->AsDouble();
		if (pendingValue != NAN) {
			if (replace_node == nullptr) {
				// Choose which node to replace on tree
				replace_node = node;
				++i;
			}
			else {
				i = children_.erase(i);
			}
			
			switch (oper_)
			{
				case Operator::ADDITION:
					sumProg += pendingValue;
					break;
				case Operator::MULTIPLICATION:
					sumProg *= pendingValue;
					break;
			}
		}
	}

	if (replace_node != nullptr) {
		ReplaceChild(new FValueNode(sumProg), replace_node);
	}

	if (children_.size() == 1) {
		return children_[0];
	}

	return this;
}

/// <summary>
/// Get the expression tree printed from this down
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
