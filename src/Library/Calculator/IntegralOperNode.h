#pragma once

#include "OperNode.h"
#include "VarValueNode.h"

class IntegralOperNode : public OperNode
{
public:
	IntegralOperNode();

	IntegralOperNode(const IntegralOperNode& other);

	void SetVariable(unique_ptr<VarValueNode> variable);

	const VarValueNode& GetVariable() const;

	void SetUpperBound(unique_ptr<ExpNode> variable);

	const ExpNode& GetUpperBound() const;

	void SetLowerBound(unique_ptr<ExpNode> variable);

	const ExpNode& GetLowerBound() const;

	void AddChild(unique_ptr<ExpNode> node) override;

	void AddChild(unique_ptr<ExpNode> node, bool overwrite);

	void InsertChild(unique_ptr<BranchNode> node);

	const ExpNode& GetChild(int index) const;

	int ChildCount() const;

	void ClearChildren();

	bool IsConstant() const override;

	bool IsConstantBy(const VarValueNode& node) const override;

	unique_ptr<ExpNode> Execute(IOperation* operation) const override;

	string Print(const IPrinter& printer) const override;

	unique_ptr<ExpNode> Clone() const override;

protected:
	bool is_determinate;
	unique_ptr<VarValueNode> variable_;
	unique_ptr<ExpNode> child_;
	unique_ptr<ExpNode> lower_;
	unique_ptr<ExpNode> upper_;
};

