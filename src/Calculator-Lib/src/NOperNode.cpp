#include <algorithm>
#include <memory>
#include <vector>

#include "include/AdditiveTerm.h"
#include "include/ExpNode.h"
#include "include/FValueNode.h"
#include "include/IValueNode.h"
#include "include/MultiplicativeTerm.h"
#include "include/NOperNode.h"
#include "include/OperNode.h"

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

//bool compareATerm(const AdditiveTerm& aterm1, AdditiveTerm& aterm2) {
//	// TODO: Better sorting
//	return !aterm1.AsExpNode()->IsNumericalValue();
//}

//bool compareMTerm(const MultiplicativeTerm &mterm1, const MultiplicativeTerm &mterm2) {
//	// TODO: Better sorting
//	
//}

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
			NOperNode *operNode = dynamic_cast<NOperNode*>(node.get());
			if (operNode != nullptr && operNode->GetOperator() == newNode->GetOperator()) {
				// newNode is a duplicate operator
				// inherit children
				// Returns values
				double childValues = newNode->InheritChildren(operNode);

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

	if ((oper_ == Operator::ADDITION && valueProg != 0) ||
		(oper_ == Operator::MULTIPLICATION && valueProg != 1)) {
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

	return newNode;
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
			if (iterATerm.CompareBase(newATerm)) {
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
			if (iterMTerm.CompareBase(newMTerm)) {
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
			switch (oper_) {
				case Operator::ADDITION:
					cache_ += "+";
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