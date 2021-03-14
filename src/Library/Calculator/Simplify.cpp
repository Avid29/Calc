#pragma once

#include <algorithm>
#include <map>

#include "AdditiveTerm.h"
#include "MultiplicativeTerm.h"
#include "Differentiator.h"
#include "Integrator.h"
#include "Simplify.h"
#include "BOperNode.h"
#include "DiffOperNode.h"
#include "FValueNode.h"
#include "IntegralOperNode.h"
#include "IValueNode.h"
#include "NOperNode.h"
#include "SinusoidalOperNode.h"
#include "TensorNode.h"
#include "UOperNode.h"
#include "VarValueNode.h"

#include "Evaluator.h"

#include "Helper.h"

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
		simpleRight->IsNumericalValue() && simpleRight->AsDouble() > 0 &&
		simpleRight->AsDouble() == floor(simpleRight->AsDouble())) {
		// if oper is Power and if right child is a positive integer
		// Expand to multiply n times
		unique_ptr<NOperNode> nOperNode = make_unique<NOperNode>('*');
		for (int i = 0; i < simpleRight->AsDouble(); i++) {
			nOperNode->AddChild(simpleLeft->Clone());
		}
		return nOperNode->Execute(this);
	}

	newNode->AddChild(move(simpleLeft));
	newNode->AddChild(move(simpleRight));

	if (node.GetOperator() == Operator::POWER) {
		return Expand(newNode.get());
	}

	return newNode;
}

unique_ptr<ExpNode> Simplifier::Execute(const DiffOperNode& node) {
	Differentiator* differentiator = new Differentiator(make_unique<VarValueNode>(node.GetVariable()));
	unique_ptr<ExpNode> result = node.GetChild(0)
		.Execute(this)->Execute(differentiator)->Execute(this);
	delete differentiator;
	return move(result);
}

unique_ptr<ExpNode> Simplifier::Execute(const FValueNode& node) {
	return node.Clone();
}

unique_ptr<ExpNode> Simplifier::Execute(const IntegralOperNode& node) {
	Integrator* integrator = new Integrator(make_unique<VarValueNode>(node.GetVariable()));
	unique_ptr<ExpNode> result = node.GetChild(0)
		.Execute(this)->Execute(integrator)->Execute(this);

	if (node.IsDeterminate())
	{
		unique_ptr<NOperNode> diffNode = make_unique<NOperNode>(Operator::ADDITION);
		Evaluator* evaluator = new Evaluator(make_unique<VarValueNode>(node.GetVariable()), node.GetUpperBound().Clone());
		diffNode->AddChild(result->Execute(evaluator));
		delete evaluator;
		evaluator = new Evaluator(make_unique<VarValueNode>(node.GetVariable()), node.GetLowerBound().Clone());
		diffNode->AddChild(Negative(result->Execute(evaluator)));
		delete evaluator;
		return diffNode->Execute(this);
	}

	delete integrator;
	return move(result);
}

unique_ptr<ExpNode> Simplifier::Execute(const IValueNode& node) {
	return node.Clone();
}

unique_ptr<ExpNode> Simplifier::Execute(const NOperNode& node) {

	if (node.GetOperator() == Operator::EQUALS)
	{
		if (node.ChildCount() > 2)
		{
			// TODO: Handle more equality children
			return node.Clone();
		}

		// Move the subtract the right-hand side from the left. Then simplify the new left-hand side.
		unique_ptr<NOperNode> newEquals = make_unique<NOperNode>(Operator::EQUALS);
		newEquals->AddChild(Subtract(node.GetChild(0), node.GetChild(1))->Execute(this));
		newEquals->AddChild(MakeValueNode(0));
		return newEquals;
	}

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

	if (newNode->ChildCount() == 0) {
		return MakeValueNode(1);
	}
	else if (newNode->ChildCount() == 1) {
		// No more operations to be run, and trim child's parent node
		return newNode->GetChild(0).Clone();
	}

	if (node.GetOperator() == Operator::MULTIPLICATION) {
		return Expand(newNode.get());
	}

	if (node.GetOperator() == Operator::ADDITION) {
		return AddTensors(newNode.get());
	}

	return newNode;
}

unique_ptr<ExpNode> Simplifier::Execute(const SinusoidalOperNode& node) {
	unique_ptr<SinusoidalOperNode> newNode = make_unique<SinusoidalOperNode>(node.GetOperator());
	newNode->AddChild(node.GetChild(0).Execute(this));

	if (newNode->GetChild(0).IsNumericalValue()) {
		switch (node.GetOperator())
		{
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
	return newNode;
}

unique_ptr<ExpNode> Simplifier::Execute(const TensorNode& node) {
	unique_ptr<TensorNode> newTensor = make_unique<TensorNode>(node.GetDimensionCount(), node.GetTensorType());
	for (int i = 0; i < node.ChildCount(); i++)
	{
		newTensor->AddChild(node.GetChild(i).Execute(this));
	}
	newTensor->EndDimension(1);
	return newTensor;
	// TODO: Proper Tensor and matrix support
}

unique_ptr<ExpNode> Simplifier::Execute(const UOperNode& node) {
	if (node.GetOperator() == Operator::RECIPROCAL) {
		// Return the reciprical, by putting to the power of -1
		return Power(*node.GetChild(0).Execute(this), -1)->Execute(this);
	}
	if (node.GetOperator() == Operator::NEGATIVE) {
		// Return negative, by multiplying -1
		return Multiply(*node.GetChild(0).Execute(this), -1)->Execute(this);
	}

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
		}
	}
	else if (node.GetOperator() == Operator::PARENTHESIS && 
		(newNode->GetChild(0).IsValue() || (node.GetParent() == nullptr || node.GetParent()->GetPriority() >= node.GetChild(0).GetPriority()))) {
		// Parenthesis are unnecessary
		return newNode->GetChild(0).Clone();
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
		unique_ptr<ExpNode> mtermNode = mTerm.AsExpNode();
		if (mtermNode->AsDouble() != 1 || (node->ChildCount() != 0 && &mTerm != &mTerms.back())) {
			// If the value is not 1 or the term isn't the last in the vector while the node is empty
			node->AddChild(move(mtermNode));
		}
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
	return make_unique<NOperNode>(*node);
}

unique_ptr<ExpNode> Simplifier::Expand(BOperNode* node) {
	unique_ptr<NOperNode> newMNode = make_unique<NOperNode>('*');

	// Check for parenthesis
	const UOperNode* uOperNode = dynamic_cast<const UOperNode*>(&node->GetChild(0));
	if (uOperNode != nullptr && uOperNode->GetOperator() == Operator::PARENTHESIS) {
		// Child is parenthesis
		// Check for multiplication
		const NOperNode& nOperNode = dynamic_cast<const NOperNode&>(uOperNode->GetChild(0));
		if (nOperNode.GetOperator() == Operator::MULTIPLICATION) {
			// Grand child is multiplication
			// Distribute
			for (int i = 0; i < nOperNode.ChildCount(); i++)
			{
				unique_ptr<BOperNode> newBNode = make_unique<BOperNode>('^');
				newBNode->AddChild(nOperNode.GetChild(i).Clone());
				newBNode->AddChild(node->GetChild(1).Clone());
				newMNode->AddChild(move(newBNode));
			}
			return newMNode->Execute(this);
		}
		return make_unique<BOperNode>(*node);
	}
	return make_unique<BOperNode>(*node);
}

unique_ptr<ExpNode> Simplifier::AddTensors(NOperNode* node) {
	map<string, unique_ptr<TensorNode>> nodeMap;
	unique_ptr<NOperNode> returnValue = make_unique<NOperNode>('+');
	for (int i = 0; i < node->ChildCount(); i++)
	{
		const TensorNode *tensorNode = dynamic_cast<const TensorNode*>(&node->GetChild(i));
		if (tensorNode != nullptr) {
			string identity = GetTensorNodeSizeIdentity(*tensorNode);
			if (nodeMap.find(identity) != nodeMap.end()) {
				unique_ptr<TensorNode> oldTensor = move(nodeMap[identity]);
				unique_ptr<TensorNode> newTensor = make_unique<TensorNode>(*oldTensor);
				newTensor->ClearChildren();
				for (int i = 0; i < tensorNode->ChildCount(); i++)
				{
					auto addition = make_unique<NOperNode>('+');
					addition->AddChild(move(oldTensor->GetChild(i).Clone()));
					addition->AddChild(move(tensorNode->GetChild(i).Clone()));
					newTensor->AddChild(move(addition->Execute(this)));
				}
				nodeMap[identity] = move(newTensor);
			}
			else {
				nodeMap[identity] = make_unique<TensorNode>(*tensorNode);
			}
		}
		else {
			returnValue->AddChild(move(node->GetChild(i).Clone()));
		}
	}

	map<string, unique_ptr<TensorNode>>::iterator it = nodeMap.begin();

	while (it != nodeMap.end())
	{
		returnValue->AddChild(move(it->second));
		it++;
	}
	return returnValue;
}
