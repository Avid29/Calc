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
		// TODO: Constant integration.
		return MakeValueNode(0);
	}

	// TODO: Increment exponent, divide by exponent
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
	// TODO: Constant integration.
	return MakeValueNode(0);
}

unique_ptr<ExpNode> Integrator::Execute(const IntegralOperNode& node) {
	// Should not hit
	throw;
	return node.Clone();
}

unique_ptr<ExpNode> Integrator::Execute(const IValueNode& node) {
	// TODO: Constant integration.
	return MakeValueNode(0);
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
		// TODO: Constant integration
		return MakeValueNode(0);
	}
	else {
		// TODO: Basic integration
		return MakeValueNode(1);
	}
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
