#pragma once

#include "ExpNode.h"

class ValueNode : public ExpNode 
{
	public:
		/// <summary>
		/// Get the value as a string
		/// </summary>
		/// <returns>The node as a string</returns>
		virtual string Print() = 0;

		virtual Priority GetPriority();
};
