#include "Integrator.h"
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

unique_ptr<ExpNode> Integrator::Execute(const BOperNode& node) {
	if (node.GetChild(0).IsConstantBy(*variable_)) {
		return ApplyConstant(node);
	}

	// Increment exponent, divide by exponent
	unique_ptr<NOperNode> mNode = make_unique<NOperNode>(Operator::MULTIPLICATION);
	unique_ptr<NOperNode> aNode = make_unique<NOperNode>(Operator::ADDITION);
	aNode->AddChild(node.GetChild(1).Clone());
	aNode->AddChild(MakeValueNode(1));
	unique_ptr<UOperNode> recipNode = make_unique<UOperNode>(Operator::RECIPROCAL);
	recipNode->AddChild(aNode->Clone());
	mNode->AddChild(move(recipNode));
	unique_ptr<BOperNode> bNode = make_unique<BOperNode>(Operator::POWER);
	bNode->AddChild(node.GetChild(0).Clone());
	bNode->AddChild(move(aNode));
	mNode->AddChild(move(bNode));
	return mNode;
}

unique_ptr<ExpNode> Integrator::Execute(const DiffOperNode& node) {
	// Should not hit
	throw;
	return node.Clone();
}

unique_ptr<ExpNode> Integrator::Execute(const FValueNode& node) {
	return ApplyConstant(node);
}

unique_ptr<ExpNode> Integrator::Execute(const IntegralOperNode& node) {
	// Should not hit
	throw;
	return node.Clone();
}

unique_ptr<ExpNode> Integrator::Execute(const IValueNode& node) {
	return ApplyConstant(node);
}

unique_ptr<ExpNode> Integrator::Execute(const NOperNode& node) {
	// TODO: Sum and Product rules.
	return node.Clone();
}

unique_ptr<ExpNode> Integrator::Execute(const SinusoidalOperNode& node) {
	// TODO: Sinusoidal integration
	return node.Clone();
}

unique_ptr<ExpNode> Integrator::Execute(const TensorNode& node) {
	// TODO: Tensor calculus
	return node.Clone();
}

unique_ptr<ExpNode> Integrator::Execute(const UOperNode& node) {
	// TODO: UOper integration
	return node.Clone();
}

unique_ptr<ExpNode> Integrator::Execute(const VarValueNode& node) {
	if (node.GetCharacter() != variable_->GetCharacter()) {
		return ApplyConstant(node);
	}
	else {
		unique_ptr<BOperNode> bNode = make_unique<BOperNode>(Operator::POWER);
		bNode->AddChild(node.Clone());
		bNode->AddChild(MakeValueNode(2));
		return bNode;
	}
}

unique_ptr<ExpNode> Integrator::ApplyConstant(const ExpNode& node)
{
	unique_ptr<NOperNode> mNode = make_unique<NOperNode>(Operator::MULTIPLICATION);
	mNode->AddChild(node.Clone());
	mNode->AddChild(variable_->Clone());
	return mNode;
}

unique_ptr<ExpNode> Integrator::ApplySumRule(const NOperNode& node) {
	// TODO: Sum rule
	return node.Clone();
}

unique_ptr<ExpNode> Integrator::ApplyProductRule(const NOperNode& node) {
	// TODO: Integration by parts
	return node.Clone();
}

unique_ptr<ExpNode> Integrator::ApplySinusoidalTable(const SinusoidalOperNode& node) {
	// TODO: Sinusoidal integration
	return node.Clone();
}
