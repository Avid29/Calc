#pragma once

#include "OperNode.h"
#include "VarValueNode.h"

class DiffOperNode : public OperNode
{
public:
	void SetVariable(unique_ptr<VarValueNode> variable);

protected:
	unique_ptr<VarValueNode> variable_;
	unique_ptr<ExpNode> child_;
};
