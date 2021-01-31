#pragma once

#include "UOperNode.h"

class SinusoidalOperNode : public UOperNode
{
public:
	/// <summary>
	/// Copy constructor
	/// </summary>
	SinusoidalOperNode(const SinusoidalOperNode& other);

	/// <summary>
	/// Create a UOperNode of operator
	/// </summary>
	/// <param name="oper">operator</param>
	SinusoidalOperNode(Operator oper);

	/// <summary>
	/// Simplifies ExpNode and children
	/// </summary>
	/// <returns>The new simplest node possible in place of this</returns>
	unique_ptr<ExpNode> Execute(IOperation* operation) const override;

	/// <summary>
	/// Get the expression tree printed from this down
	/// </summary>
	/// <returns>The expression tree as a string</returns>
	string Print(const IPrinter& printer) const override;

	/// <summary>
	/// Gets a clone of this
	/// </summary>
	unique_ptr<ExpNode> Clone() const override;
};
