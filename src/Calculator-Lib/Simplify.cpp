#pragma once

#include <algorithm>

#include "AdditiveTerm.h"
#include "MultiplicativeTerm.h"
#include "Differentiator.h"
#include "Simplify.h"
#include "BOperNode.h"
#include "DiffOperNode.h"
#include "FValueNode.h"
#include "IValueNode.h"
#include "NOperNode.h"
#include "UOperNode.h"
#include "VarValueNode.h"

unique_ptr<ExpNode> Simplifier::Execute(const BOperNode& node) {
	// Always returns a clone or replacement
	unique_ptr<BOperNode> newNode = make_unique<BOperNode>(node.GetOperator());

	unique_ptr<ExpNode> simpleLeft = node.GetChild(0).Execute(this);
	unique_ptr<ExpNode> simpleRight = node.GetChild(1).Execute(this);

	// Returns 1 because anything to the power of 0 is 1
	if (node.GetOperator() == Operator::POWER && simpleRight->AsDouble() == 0) {
		return MakeValueNode(1);
	}

	if (simpleLeft->IsNumericalValue() && simpleRight->IsNumericalValue()) {
		switch (node.GetOperator())
		{
		case Operator::POWER:
			// Get a ValueNode for left to the power of right
			return MakeValueNode(pow(simpleLeft->AsDouble(), simpleRight->AsDouble()));
		}
	}

	if (node.GetOperator() == Operator::POWER &&
		simpleRight->IsNumericalValue() &&
		simpleRight->AsDouble() == floor(simpleRight->AsDouble())) {
		// if oper is Power and if right child is an int 
		// Expand to multiply n times
		unique_ptr<NOperNode> nOperNode = make_unique<NOperNode>('*');
		for (int i = 0; i < simpleRight->AsDouble(); i++) {
			nOperNode->AddChild(simpleLeft->Clone());
		}
		return nOperNode->Execute(this);
	}

	newNode->AddChild(move(simpleLeft));
	newNode->AddChild(move(simpleRight));

	return newNode;
}

unique_ptr<ExpNode> Simplifier::Execute(const DiffOperNode& node) {
	// TODO: Differentiate
	Differentiator* differentiator = new Differentiator(make_unique<VarValueNode>(node.GetVariable()));
	unique_ptr<ExpNode> result = node.GetChild(0).Execute(differentiator);
	delete differentiator;
	return move(result);
}

unique_ptr<ExpNode> Simplifier::Execute(const FValueNode& node) {
	return node.Clone();
}

unique_ptr<ExpNode> Simplifier::Execute(const IValueNode& node) {
	return node.Clone();
}

unique_ptr<ExpNode> Simplifier::Execute(const NOperNode& node) {
	// TODO: Move Simplify to operation

	// Running total of value node children
	double valueProg = 0;
	if (node.GetOperator() == Operator::MULTIPLICATION) {
		valueProg = 1;
	}

	// Always returns a clone or replacement
	unique_ptr<NOperNode> newNode = make_unique<NOperNode>(node.GetOperator());

	// Iterates whole vector
	for (int i = 0; i < node.ChildCount(); i++) {
		// Doesn't update node in children_
		unique_ptr<ExpNode> simplified_child = node.GetChild(i).Execute(this);

		if (simplified_child->IsNumericalValue()) {
			// Add node value to total value progress
			switch (node.GetOperator())
			{
			case Operator::ADDITION:
				valueProg += simplified_child->AsDouble();
				break;
			case Operator::MULTIPLICATION:
				valueProg *= simplified_child->AsDouble();
				break;
			}
		}
		else {
			double childValues = newNode->TryInheritChildren(simplified_child.get());
			if (childValues != -1) {
				switch (node.GetOperator())
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
				newNode->AddChild(move(simplified_child));
			}
		}
	}

	if (node.GetOperator() == Operator::MULTIPLICATION && valueProg == 0) {
		// Because one multiplicative term is zero
		// The enitre node is zero
		return MakeValueNode(0);
	}

	if (newNode->ChildCount() == 0 ||
		((node.GetOperator() == Operator::ADDITION && valueProg != 0) ||
			(node.GetOperator() == Operator::MULTIPLICATION && valueProg != 1))) {
		// valueProg is not the default, so it should be added
		newNode->AddChild(MakeValueNode(valueProg));
	}

	if (newNode->ChildCount() == 1) {
		return newNode->GetChild(0).Clone();
	}

	switch (node.GetOperator())
	{
	case Operator::ADDITION:
		SimplifyATerms(newNode.get());
		break;
	case Operator::MULTIPLICATION:
		SimplifyMTerms(newNode.get());
		break;
	}

	if (node.GetOperator() == Operator::MULTIPLICATION) {
		return Expand(newNode.get());
	}

	return newNode;
}

unique_ptr<ExpNode> Simplifier::Execute(const UOperNode& node) {
	// Always returns a clone or replacement
	unique_ptr<UOperNode> newNode = make_unique<UOperNode>(node.GetOperator());
	newNode->AddChild(node.GetChild(0).Execute(this));

	if (newNode->GetChild(0).IsNumericalValue()) {
		switch (node.GetOperator())
		{
		case Operator::POSITIVE:
		case Operator::PARENTHESIS:
			return MakeValueNode(newNode->GetChild(0).AsDouble());
		case Operator::NEGATIVE:
			return MakeValueNode(-newNode->GetChild(0).AsDouble());
		case Operator::RECIPROCAL:
			return MakeValueNode(1 / newNode->GetChild(0).AsDouble());
		case Operator::SINE:
			return MakeValueNode(sin(newNode->GetChild(0).AsDouble()));
		case Operator::COSINE:
			return MakeValueNode(cos(newNode->GetChild(0).AsDouble()));
		case Operator::TANGENT:
			return MakeValueNode(tan(newNode->GetChild(0).AsDouble()));
		case Operator::COSECANT:
			return MakeValueNode(1 / sin(newNode->GetChild(0).AsDouble()));
		case Operator::SECANT:
			return MakeValueNode(1 / cos(newNode->GetChild(0).AsDouble()));
		case Operator::COTANGENT:
			return MakeValueNode(1 / tan(newNode->GetChild(0).AsDouble()));
		}
	}
	else if (node.GetOperator() == Operator::PARENTHESIS &&
		(node.GetParent() == nullptr || node.GetParent()->GetPriority() >= node.GetChild(0).GetPriority())) {
		// Parenthesis are unnecessary
		return move(newNode->GetChild(0).Clone());
	}
	return newNode;
}

unique_ptr<ExpNode> Simplifier::Execute(const VarValueNode& node) {
	return node.Clone();
}

void Simplifier::SimplifyATerms(NOperNode *node) {
	vector<AdditiveTerm> aTerms;

	for (int i = 0; i < node->ChildCount(); i++) {
		// Gets current child as AdditiveTerm
		AdditiveTerm newATerm(node->GetChild(i));

		bool foundLikeBase = false;

		// Compares to previous AdditiveTerms
		for (AdditiveTerm& iterATerm : aTerms) {
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
	node->ClearChildren();
	for (AdditiveTerm& aTerm : aTerms) {
		node->AddChild(aTerm.AsExpNode());
	}
}

void Simplifier::SimplifyMTerms(NOperNode* node) {
	vector<MultiplicativeTerm> mTerms;

	for (int i = 0; i < node->ChildCount(); i++) {
		// Gets current child as MultiplicativeTerm
		MultiplicativeTerm newMTerm(node->GetChild(i));

		bool foundLikeBase = false;

		// Compares to previous MultiplicativeTerms
		for (MultiplicativeTerm& iterMTerm : mTerms) {
			if (iterMTerm == newMTerm) {
				iterMTerm.AddToExponent(&newMTerm, this);
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
	node->ClearChildren();
	for (MultiplicativeTerm& mTerm : mTerms) {
		node->AddChild(mTerm.AsExpNode());
	}
}

unique_ptr<ExpNode> Simplifier::Expand(NOperNode* node) {
	unique_ptr<NOperNode> newANode = make_unique<NOperNode>('+');

	// Check for parenthesis
	const UOperNode* uOperNode = dynamic_cast<const UOperNode*>(&node->GetChild(node->ChildCount()-1));
	if (uOperNode != nullptr && uOperNode->GetOperator() == Operator::PARENTHESIS) {
		// Child is parenthesis
		// Check for addition
		const NOperNode& nOperNode = dynamic_cast<const NOperNode&>(uOperNode->GetChild(0));
		if (nOperNode.GetOperator() == Operator::ADDITION) {
			// Grand child is addition
			// Distribute
			for (int i = 0; i < nOperNode.ChildCount(); i++)
			{
				unique_ptr<NOperNode> newMNode = make_unique<NOperNode>('*');
				newMNode->AddChild(nOperNode.GetChild(i).Clone());
				for (int i = 0; i < node->ChildCount(); i++)
				{
					if (&node->GetChild(i) != uOperNode) {
						newMNode->AddChild(node->GetChild(i).Clone());
					}
				}
				newANode->AddChild(move(newMNode));
			}
			return newANode->Execute(this);
		}
		return make_unique<NOperNode>(*node);
	}
	else {
		return make_unique<NOperNode>(*node);
	}
}
