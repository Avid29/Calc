#pragma once

#include "IOperation.h"
#include "ValueNode.h"

class Evaluator : public IOperation
{
public:
	Evaluator(unique_ptr<VarValueNode> variable, unique_ptr<ExpNode> substitute) {
		variable_ = move(variable);
		substitute_ = move(substitute);
	}

	unique_ptr<ExpNode> Execute(const BOperNode&) override;

	unique_ptr<ExpNode> Execute(const DiffOperNode&) override;

	unique_ptr<ExpNode> Execute(const FValueNode&) override;

	unique_ptr<ExpNode> Execute(const IntegralOperNode& node) override;

	unique_ptr<ExpNode> Execute(const IValueNode&) override;

	unique_ptr<ExpNode> Execute(const NOperNode&) override;

	unique_ptr<ExpNode> Execute(const SinusoidalOperNode& node) override;

	unique_ptr<ExpNode> Execute(const TensorNode& node) override;

	unique_ptr<ExpNode> Execute(const UOperNode&) override;

	unique_ptr<ExpNode> Execute(const VarValueNode&) override;

private:
	unique_ptr<VarValueNode> variable_;
	unique_ptr<ExpNode> substitute_;
};

