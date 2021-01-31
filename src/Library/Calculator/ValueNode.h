#pragma once

#include "ExpNode.h"

class ValueNode : public ExpNode 
{
	public:
		/// <summary>
		/// Checks if node is a value
		/// </summary>
		/// <returns>true if node is a value</returns>
		bool IsValue() const override;

		/// <summary>
		/// Gets the priority of the node by operation or type
		/// </summary>
		/// <returns>The priority of depth on the tree</returns>
		Priority GetPriority() const override;

		/// <summary>
		/// Gets a clone of this
		/// </summary>
		virtual unique_ptr<ExpNode> Clone() const = 0;

		virtual bool IsConstant() const override;

		virtual bool IsConstantBy(const VarValueNode& node) const override;
};