#pragma once

#include "IOperation.h"

class Differentiator : public IOperation
{
public:
	Differentiator(unique_ptr<VarValueNode> variable) {
		variable_ = move(variable);
	}

	unique_ptr<ExpNode> Execute(const BOperNode&) override;

	unique_ptr<ExpNode> Execute(const DiffOperNode&) override;

	unique_ptr<ExpNode> Execute(const FValueNode&) override;

	unique_ptr<ExpNode> Execute(const IValueNode&) override;

	unique_ptr<ExpNode> Execute(const NOperNode&) override;

	unique_ptr<ExpNode> Execute(const UOperNode&) override;

	unique_ptr<ExpNode> Execute(const VarValueNode&) override;

private:
	unique_ptr<ExpNode> ApplySumRule(const NOperNode& node);

	unique_ptr<ExpNode> ApplyProductRule(const NOperNode& node);

	unique_ptr<VarValueNode> variable_;
};
