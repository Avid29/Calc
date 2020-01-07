#pragma once

#include "ExpNode.h"

class ValueNode : public ExpNode 
{
	public:
		virtual string Print() = 0;

		virtual Priority GetPriority();
};
