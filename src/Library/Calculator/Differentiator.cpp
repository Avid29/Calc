#include "Differentiator.h"
#include "AdditiveTerm.h"
#include "MultiplicativeTerm.h"
#include "Simplify.h"
#include "BOperNode.h"
#include "DiffOperNode.h"
#include "FValueNode.h"
#include "IntegralOperNode.h"
#include "IValueNode.h"
#include "SinusoidalOperNode.h"
#include "TensorNode.h"
#include "NOperNode.h"
#include "UOperNode.h"
#include "VarValueNode.h"

#include "Helper.h"

unique_ptr<ExpNode> Differentiator::Execute(const BOperNode& node) {
	if (node.GetChild(0).IsConstantBy(*variable_)) {
		return MakeValueNode(0);
	}

	// Multiply by exponent, decrement exponent
	const auto coefficient = node.GetChild(1);
	const auto base = node.GetChild(0);
	const auto exponent = *Add(node.GetChild(1), -1);
	return Multiply(coefficient, *Power(base, exponent));
}

unique_ptr<ExpNode> Differentiator::Execute(const DiffOperNode& node) {
	// Should not hit
	throw;
	return node.Clone();
}

unique_ptr<ExpNode> Differentiator::Execute(const FValueNode& node) {
	return MakeValueNode(0);
}

unique_ptr<ExpNode> Differentiator::Execute(const IntegralOperNode& node) {
	// Should not hit
	throw;
	return node.Clone();
}

unique_ptr<ExpNode> Differentiator::Execute(const IValueNode& node) {
	return MakeValueNode(0);
}

unique_ptr<ExpNode> Differentiator::Execute(const NOperNode& node) {
	switch (node.GetOperator())
	{
	case Operator::ADDITION:
		return ApplySumRule(node);
	case Operator::MULTIPLICATION:
		return ApplyProductRule(node);
	}

	return node.Clone();
}

unique_ptr<ExpNode> Differentiator::Execute(const SinusoidalOperNode& node) {
	// Apply ChainRule
	auto coefficient = *node.GetChild(0).Execute(this);
	// Apply derivative table
	auto sinFunc = *ApplySinusoidalTable(node);
	return Multiply(coefficient, sinFunc);
}

unique_ptr<ExpNode> Differentiator::Execute(const TensorNode& node) {
	// TODO: Tensor calculus
	return node.Clone();
}

unique_ptr<ExpNode> Differentiator::Execute(const UOperNode& node) {
	// TODO: UOper differentiation
	return node.Clone();
}

unique_ptr<ExpNode> Differentiator::Execute(const VarValueNode& node) {
	if (node.GetCharacter() != variable_->GetCharacter()) {
		return MakeValueNode(0);
	}
	else {
		return MakeValueNode(1);
	}
}

unique_ptr<ExpNode> Differentiator::ApplySumRule(const NOperNode& node) {
	unique_ptr<NOperNode> nNode = make_unique<NOperNode>(node.GetOperator());
	for (int i = 0; i < node.ChildCount(); i++)
	{
		nNode->AddChild(node.GetChild(i).Execute(this));
	}
	return move(nNode);
}

unique_ptr<ExpNode> Differentiator::ApplyProductRule(const NOperNode& node) {
	unique_ptr<NOperNode> aNode = make_unique<NOperNode>(Operator::ADDITION);
	for (int i = 0; i < node.ChildCount(); i++) {
		unique_ptr<NOperNode> mNode = make_unique<NOperNode>(Operator::MULTIPLICATION);
		mNode->AddChild(node.GetChild(i).Execute(this));
		for (int j = 0; j < node.ChildCount(); j++) {
			if (j != i) {
				mNode->AddChild(node.GetChild(j).Clone());
			}
		}
		aNode->AddChild(move(mNode));
	}
	return aNode;
}

unique_ptr<ExpNode> Differentiator::ApplySinusoidalTable(const SinusoidalOperNode& node) {
	unique_ptr<OperNode> newNode;

	switch (node.GetOperator())
	{
	case Operator::SINE:
		newNode = make_unique<SinusoidalOperNode>(Operator::COSINE);
		newNode->AddChild(node.GetChild(0).Clone());
		return newNode;
	case Operator::COSINE:
		newNode = make_unique<SinusoidalOperNode>(Operator::SINE);
		newNode->AddChild(node.GetChild(0).Clone());
		return Negative(move(newNode));
	default:
		return node.Clone();
	}
}
