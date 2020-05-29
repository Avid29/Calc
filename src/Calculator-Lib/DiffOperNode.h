#pragma once

#include "OperNode.h"
#include "VarValueNode.h"

class DiffOperNode : public OperNode
{
public:
	DiffOperNode();

	DiffOperNode(const DiffOperNode& other);

	void SetVariable(unique_ptr<VarValueNode> variable);

	const VarValueNode& GetVariable() const;

	void AddChild(unique_ptr<ExpNode> node) override;

	void AddChild(unique_ptr<ExpNode> node, bool overwrite);

	void InsertChild(unique_ptr<OperNode> node);

	const ExpNode& GetChild(int index) const;
	
	int ChildCount() const;

	void ClearChildren();

	bool IsConstant() const override;

	bool IsConstantBy(const VarValueNode& node) const override;

	unique_ptr<ExpNode> Execute(IOperation* operation) const override;

	string Print(const IPrinter& printer) const override;

	unique_ptr<ExpNode> Clone() const override;

protected:
	unique_ptr<VarValueNode> variable_;
	unique_ptr<ExpNode> child_;
};
