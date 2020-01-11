#include <algorithm>
#include <memory>
#include <vector>

#include "../include/ExpNode.h"
#include "../include/FValueNode.h"
#include "../include/IValueNode.h"
#include "../include/MultiplicativeTerm.h"
#include "../include/NOperNode.h"
#include "../include/OperNode.h"

using namespace std;

#pragma region Constrcutors

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

#pragma endregion

#pragma region TreeBuilding

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
void NOperNode::ReplaceChild(ExpNode *newNode, ExpNode *oldNode) {
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
#pragma endregion

/// <summary>
/// Gets child at index
/// </summary>
/// <returns>child at index</returns>
ExpNode *NOperNode::GetChild(int index) {
	return children_[index];
}

#pragma region Simplify

bool compareMTerm(MultiplicativeTerm *mterm1, MultiplicativeTerm *mterm2) {
	return mterm1->AsExpNode()->IsNumericalValue();
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

	if (oper_ == Operator::MULTIPLICATION && valueProg == 0) {
		// Because one multiplicative term is zero
		// The enitre node is zero
		return GetValueNode(0);
	}

	if ((oper_ == Operator::ADDITION && valueProg != 0) ||
		(oper_ == Operator::MULTIPLICATION && valueProg != 1)) {
		// valueProg is not the default, so it should be added
		newNode->AddChild(GetValueNode(valueProg));
	}

	if (newNode->children_.size() == 1) {
		return newNode->children_[0];
	}

	switch (oper_)
	{
		case Operator::ADDITION:
			// TODO: Simplify A terms
			break;
		case Operator::MULTIPLICATION:
			newNode->SimplifyMTerms();
			break;
	}

	return newNode;
}

void NOperNode::SimplifyMTerms() {

	vector<MultiplicativeTerm*> mTerms;
	
	for (ExpNode *child : children_) {
		// Gets current child as MultiplicativeTerm
		MultiplicativeTerm *newMTerm = new MultiplicativeTerm(child);

		bool foundBase = false;

		// Compares to previous MultiplicativeTerms
		if (mTerms.size() != 0) {
			auto i = begin(mTerms);
			while (i != end(mTerms))
			{
				MultiplicativeTerm *iterMTerm = *i;
				if (iterMTerm->CompareBase(*newMTerm)) {
					iterMTerm->AddToExponent(newMTerm);
					foundBase = true;
					break;
				}
				++i;
			}
		}

		// Adds to list if there were no MTerms with shared base
		if (!foundBase)
			mTerms.push_back(newMTerm);
	}

	sort(mTerms.begin(), mTerms.end(), compareMTerm);

	// Resets children then gets children from MTerms
	children_.clear();
	for (MultiplicativeTerm *mTerm : mTerms) {
		children_.push_back(mTerm->AsExpNode());
	}
}

#pragma endregion

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
					// All remaining multiplication will be implied
					break;
			}
		}
		ExpNode *node = children_[i];
		cache_ += node->Print();	
	}
	return cache_;
}
