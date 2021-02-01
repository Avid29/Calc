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

#include "InternalPrinter.h"

#include "Helper.h"

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
		return Multiply(*Power(*node.Clone(), 2), .5);
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
	InternalPrinter printer = InternalPrinter();

	size_t partCount = node.ChildCount() - 1;

	// Get u and du
	const ExpNode& du = node.GetChild(partCount);
	unique_ptr<ExpNode> u = du.Execute(this);

	// Get dvs and vs
	unique_ptr<ExpNode>* dvs = new unique_ptr<ExpNode>[partCount];
	const ExpNode** vs = new const ExpNode*[partCount];
	for (int i = 0; i < partCount; i++)
	{
		vs[i] = &node.GetChild(i);
		dvs[i] = vs[i]->Execute(diff);
	}

	// Sum u*vs and combinatoric integrals
	unique_ptr<NOperNode> aNode = make_unique<NOperNode>(Operator::ADDITION);

	// u*vs
	unique_ptr<NOperNode> mNode = make_unique<NOperNode>(Operator::MULTIPLICATION);
	mNode->AddChild(u->Clone());
	for (int i = 0; i < partCount; i++)
	{
		mNode->AddChild(vs[i]->Clone());
	}
	aNode->AddChild(move(mNode));

	// Combinatoric integrals
	for (int i = 0; i < partCount; i++)
	{
		unique_ptr<IntegralOperNode> intNode = make_unique<IntegralOperNode>();
		mNode = make_unique<NOperNode>(Operator::MULTIPLICATION);
		intNode->SetVariable(make_unique<VarValueNode>(variable_->GetCharacter()));
		mNode->AddChild(u->Clone());
		for (int j = 0; j < partCount; j++)
		{
			if (i == j)
				mNode->AddChild(dvs[j]->Clone());
			else
				mNode->AddChild(vs[j]->Clone());
		}
		intNode->AddChild(move(mNode));
		aNode->AddChild(Negative(*intNode));
	}

	delete diff;
	return aNode;
}

unique_ptr<ExpNode> Integrator::ApplySinusoidalTable(const SinusoidalOperNode& node) {
	// TODO: Sinusoidal integration
	return node.Clone();
}
