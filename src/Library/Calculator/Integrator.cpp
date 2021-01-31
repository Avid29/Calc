#include "Integrator.h"
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
	switch (node.GetOperator())
	{
	case Operator::ADDITION:
		return ApplySumRule(node);
	case Operator::MULTIPLICATION:
		return ApplyProductRule(node);
	}

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
		bNode->AddChild(MakeValueNode(1));
		return Execute(*bNode);
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
	unique_ptr<NOperNode> nNode = make_unique<NOperNode>(node.GetOperator());
	for (int i = 0; i < node.ChildCount(); i++)
	{
		nNode->AddChild(node.GetChild(i).Execute(this));
	}
	return move(nNode);
}

unique_ptr<ExpNode> Integrator::ApplyProductRule(const NOperNode& node) {
	// TODO: Nary Integration by parts
	// \int{u'vwx} = uvwx - \int{uv'wx} - \int{uvw'x} - \int{uvwx'}

	Differentiator* diff = new Differentiator(make_unique<VarValueNode>(variable_->GetCharacter()));

	const ExpNode& u = node.GetChild(0);
	const ExpNode& dv = node.GetChild(1);
	unique_ptr<ExpNode> du = u.Execute(diff);
	unique_ptr<ExpNode> v = dv.Execute(this);

	unique_ptr<NOperNode> aNode = make_unique<NOperNode>(Operator::ADDITION);
	// u * v
	unique_ptr<NOperNode> mNode = make_unique<NOperNode>(Operator::MULTIPLICATION);
	mNode->AddChild(u.Clone());
	mNode->AddChild(v->Clone());
	aNode->AddChild(move(mNode));

	// - \int{ du * v }
	unique_ptr<UOperNode> negNode = make_unique<UOperNode>(Operator::NEGATIVE);
	unique_ptr<IntegralOperNode> intNode = make_unique<IntegralOperNode>();
	intNode->SetVariable(make_unique<VarValueNode>(variable_->GetCharacter()));
	unique_ptr<NOperNode> m2Node = make_unique<NOperNode>(Operator::MULTIPLICATION);
	m2Node->AddChild(du->Clone());
	m2Node->AddChild(v->Clone());
	intNode->AddChild(move(m2Node));
	negNode->AddChild(move(intNode));

	// u * v - \int{ du * v }
	aNode->AddChild(move(negNode));

	delete diff;
	return aNode;
}

unique_ptr<ExpNode> Integrator::ApplySinusoidalTable(const SinusoidalOperNode& node) {
	// TODO: Sinusoidal integration
	return node.Clone();
}
