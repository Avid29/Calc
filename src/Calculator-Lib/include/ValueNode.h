#pragma once

#include "ExpNode.h"

class ValueNode : public ExpNode 
{
	public:
		/// <summary>
		/// Gets the value as a string
		/// </summary>
		/// <returns>The node as a string</returns>
		virtual string Print() = 0;
		
		/// <summary>
		/// Checks if node can be represented as a double
		/// </summary>
		/// <returns>true if node can be represented as a double</returns>
		virtual bool IsNumericalValue() = 0;

		/// <summary>
		/// Gets this as a double, if possible
		/// </summary>
		/// <returns>this node as a double value or NAN if not possible</returns>
		virtual double AsDouble() = 0;

		/// <summary>
		/// Simplifies ExpNode
		/// </summary>
		/// <returns>The new simplest node possible in place of this</returns>
		ExpNode* Simplify();

		/// <summary>
		/// Gets the priority of the node by operation or type
		/// </summary>
		/// <returns>The priority of depth on the tree</returns>
		Priority GetPriority();
};
