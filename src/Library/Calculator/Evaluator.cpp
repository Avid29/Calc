#include "Evaluator.h"
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
#include "ValueNode.h"
#include "VarValueNode.h"

#include "InternalPrinter.h"

#include "Helper.h"

unique_ptr<ExpNode> Evaluator::Execute(const BOperNode& node) {
	unique_ptr<BOperNode> bOper = make_unique<BOperNode>(node.GetOperator());
	bOper->AddChild(node.GetChild(0).Execute(this));
	bOper->AddChild(node.GetChild(1).Execute(this));
	return bOper;
}

unique_ptr<ExpNode> Evaluator::Execute(const DiffOperNode& node) {
	// Shouldn't happen
	return node.Clone();
}

unique_ptr<ExpNode> Evaluator::Execute(const FValueNode& node) {
	return node.Clone();
}

unique_ptr<ExpNode> Evaluator::Execute(const IntegralOperNode& node) {
	// Shouldn't happen
	return node.Clone();
}

unique_ptr<ExpNode> Evaluator::Execute(const IValueNode& node) {
	return node.Clone();
}

unique_ptr<ExpNode> Evaluator::Execute(const NOperNode& node) {
	unique_ptr<NOperNode> nOper = make_unique<NOperNode>(node.GetOperator());
	for (int i = 0; i < node.ChildCount(); i++)
	{
		nOper->AddChild(node.GetChild(i).Execute(this));
	}
	return nOper;
}

unique_ptr<ExpNode> Evaluator::Execute(const SinusoidalOperNode& node) {
	unique_ptr<SinusoidalOperNode> uOper = make_unique<SinusoidalOperNode>(node.GetOperator());
	uOper->AddChild(node.GetChild(0).Execute(this));
	return uOper;
}

unique_ptr<ExpNode> Evaluator::Execute(const TensorNode& node) {
	unique_ptr<TensorNode> tNode = make_unique<TensorNode>(node.GetDimensionCount(), node.GetTensorType());
	for (int i = 0; i < node.ChildCount(); i++)
	{
		tNode->AddChild(node.GetChild(i).Execute(this));
	}
	tNode->EndDimension(1);
	return tNode;
}

unique_ptr<ExpNode> Evaluator::Execute(const UOperNode& node) {
	unique_ptr<UOperNode> uOper = make_unique<UOperNode>(node.GetOperator());
	uOper->AddChild(node.GetChild(0).Execute(this));
	return uOper;
}

unique_ptr<ExpNode> Evaluator::Execute(const VarValueNode& node) {
	if (node.GetCharacter() == variable_->GetCharacter())
	{
		return substitute_->Clone();
	}
	else
	{
		return node.Clone();
	}
}
