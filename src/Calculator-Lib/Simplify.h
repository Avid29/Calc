#pragma once

#include <memory>

#include "IOperation.h"

class Simplify : public IOperation
{
public:
	unique_ptr<ExpNode> Execute(const BOperNode& node);

	unique_ptr<ExpNode> Execute(const DiffOperNode& node);

	unique_ptr<ExpNode> Execute(const FValueNode& node);

	unique_ptr<ExpNode> Execute(const IValueNode& node);

	unique_ptr<ExpNode> Execute(const NOperNode& node);

	unique_ptr<ExpNode> Execute(const UOperNode& node);

	unique_ptr<ExpNode> Execute(const VarValueNode& node);

private:
	void SimplifyATerms(NOperNode* node);

	void SimplifyMTerms(NOperNode* node);
};
