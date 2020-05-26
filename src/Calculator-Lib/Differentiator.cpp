#include "Differentiator.h"
#include "AdditiveTerm.h"
#include "MultiplicativeTerm.h"
#include "Simplify.h"
#include "BOperNode.h"
#include "DiffOperNode.h"
#include "FValueNode.h"
#include "IValueNode.h"
#include "NOperNode.h"
#include "UOperNode.h"
#include "VarValueNode.h"

unique_ptr<ExpNode> Differentiator::Execute(const BOperNode& node) {
	// TODO: Multiply by exponent, subtract one from exponent
	return node.Clone();
}

unique_ptr<ExpNode> Differentiator::Execute(const DiffOperNode& node) {
	// TODO: Should not hit
	return node.Clone();
}

unique_ptr<ExpNode> Differentiator::Execute(const FValueNode& node) {
	return MakeValueNode(0);
}

unique_ptr<ExpNode> Differentiator::Execute(const IValueNode& node) {
	return MakeValueNode(0);
}

unique_ptr<ExpNode> Differentiator::Execute(const NOperNode& node) {
	// TODO: Product rule (multiplication) or differentiate all children (addition)
	switch (node.GetOperator())
	{
	case Operator::ADDITION:
		return ApplySumRule(node);
	case Operator::MULTIPLICATION:
		return ApplyProductRule(node);
	}

	return node.Clone();
}

unique_ptr<ExpNode> Differentiator::Execute(const UOperNode& node) {
	// TODO: Sinusoidal differentiation
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
	return node.Clone();
}
