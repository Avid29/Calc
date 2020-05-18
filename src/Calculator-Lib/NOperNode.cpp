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
void NOperNode::InsertChild(unique_ptr<OperNode> node) {
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
	return children_.size();
}

#pragma region Simplify

/// <summary>
/// Simplifies ExpNode and children
/// </summary>
/// <returns>The new simplest node possible in place of this</returns>
unique_ptr<ExpNode> NOperNode::Simplify() const {
	// Running total of value node children
	double valueProg = 0;
	if (oper_ == Operator::MULTIPLICATION) {
		valueProg = 1;
	}

	// Always returns a clone or replacement
	unique_ptr<NOperNode> newNode = make_unique<NOperNode>(oper_);

	// Iterates whole vector
	for (auto &child : children_) {
		// Doesn't update node in children_
		unique_ptr<ExpNode> node = child->Simplify();

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
			double childValues = newNode->TryInheritChildren(node.get());
			if (childValues != -1) {
				switch (oper_)
				{
					case Operator::ADDITION:
						valueProg += childValues;
						break;
					case Operator::MULTIPLICATION:
						valueProg *= childValues;
						break;
				}
			}
			else {
				newNode->AddChild(move(node));
			}
		}
	}

	if (oper_ == Operator::MULTIPLICATION && valueProg == 0) {
		// Because one multiplicative term is zero
		// The enitre node is zero
		return MakeValueNode(0);
	}

	if (newNode->children_.size() == 0 ||
		((oper_ == Operator::ADDITION && valueProg != 0) ||
		(oper_ == Operator::MULTIPLICATION && valueProg != 1))) {
		// valueProg is not the default, so it should be added
		newNode->AddChild(MakeValueNode(valueProg));
	}

	if (newNode->children_.size() == 1) {
		return move(newNode->children_[0]);
	}

	switch (oper_)
	{
		case Operator::ADDITION:
			newNode->SimplifyATerms();
			break;
		case Operator::MULTIPLICATION:
			newNode->SimplifyMTerms();
			break;
	}

	if (oper_ == Operator::MULTIPLICATION) {
		return newNode->Expand();
	}

	return newNode;
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

/// <summary>
/// Gets expanded version of node
/// </summary>
/// <returns> Expanded version of this</returns>
unique_ptr<ExpNode> NOperNode::Expand() {
	unique_ptr<NOperNode> newANode = make_unique<NOperNode>('+');

	// Check for parenthesis
	const UOperNode *uOperNode = dynamic_cast<const UOperNode*>(children_.back().get());
	if (uOperNode != nullptr && uOperNode->GetOperator() == Operator::PARENTHESIS) {
		// Child is parenthesis
		// Check for addition
		const NOperNode &nOperNode = dynamic_cast<const NOperNode &>(uOperNode->GetChild(0));
		if (nOperNode.GetOperator() == Operator::ADDITION) {
			// Grand child is addition
			// Distribute
			for (auto &child : nOperNode.children_)
			{
				unique_ptr<NOperNode> newMNode = make_unique<NOperNode>('*');
				newMNode->AddChild(child->Clone());
				for (auto &otherChild : children_)
				{
					if (otherChild.get() != uOperNode) {
						newMNode->AddChild(otherChild->Clone());
					}
				}
				newANode->AddChild(move(newMNode));
			}
			return newANode->Simplify();
		}
		return make_unique<NOperNode>(*this);
	}
	else {
		return make_unique<NOperNode>(*this);
	}
}

/// <summary>
/// Sorts children into ATerms and applies properties to simplify them
/// </summary>
void NOperNode::SimplifyATerms() {

	vector<AdditiveTerm> aTerms;

	for (const unique_ptr<ExpNode> &child : children_) {
		// Gets current child as AdditiveTerm
		AdditiveTerm newATerm(*child);

		bool foundLikeBase = false;

		// Compares to previous AdditiveTerms
		for (AdditiveTerm &iterATerm : aTerms) {
			if (iterATerm == newATerm) {
				iterATerm.AddToCoefficient(&newATerm);
				foundLikeBase = true;
				break;
			}
		}

		// Adds to list if there were no ATerms with shared base
		if (!foundLikeBase) {
			aTerms.push_back(move(newATerm));
		}
	}

	//sort(aTerms.begin(), aTerms.end(), compareATerm);

	// Resets children then gets children from ATerms
	children_.clear();
	for (AdditiveTerm &aTerm : aTerms) {
		children_.push_back(aTerm.AsExpNode());
	}
}

/// <summary>
/// Sorts children into MTerms and applies properties to simplify them
/// </summary>
void NOperNode::SimplifyMTerms() {

	vector<MultiplicativeTerm> mTerms;
	
	for (auto &child : children_) {
		// Gets current child as MultiplicativeTerm
		MultiplicativeTerm newMTerm(*child);

		bool foundLikeBase = false;

		// Compares to previous MultiplicativeTerms
		for (MultiplicativeTerm &iterMTerm : mTerms) {
			if (iterMTerm == newMTerm) {
				iterMTerm.AddToExponent(&newMTerm);
				foundLikeBase = true;
				break;
			}
		}

		// Adds to list if there were no MTerms with shared base
		if (!foundLikeBase)
			mTerms.push_back(move(newMTerm));
	}

	sort(mTerms.begin(), mTerms.end());

	// Resets children then gets children from MTerms
	children_.clear();
	for (MultiplicativeTerm &mTerm : mTerms) {
		children_.push_back(mTerm.AsExpNode());
	}
}

#pragma endregion

/// <summary>
/// Gets the expression tree printed from this down
/// </summary>
/// <returns>The expression tree as a string</returns>
string NOperNode::Print() const {
	string cache_;
	for (unsigned int i = 0; i < children_.size(); i++) {
		if (i != 0) {
			const UOperNode *uOperNode = dynamic_cast<const UOperNode*>(children_[i].get());
			switch (oper_) {
				case Operator::ADDITION:
					if (isnan(children_[i]->AsDouble()) ?
						!(uOperNode != nullptr &&
							uOperNode->GetOperator() != Operator::NEGATIVE) :
						children_[i]->AsDouble() > 0) {
						// If child is not unary minus or a negative value
						cache_ += "+";
					}
					break;
				case Operator::MULTIPLICATION:
					// All remaining multiplication will be implied
					break;
			}
		}
		cache_ += children_[i]->Print();
	}
	return cache_;
}

/// <summary>
/// Gets a clone of this
/// </summary>
unique_ptr<ExpNode> NOperNode::Clone() const {
	return make_unique<NOperNode>(*this);
}