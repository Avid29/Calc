#pragma once

#include "ValueNode.h"

class VarValueNode : public ValueNode {

	public:
		/// <summary>
		/// Creates a VarValueNode with variable var
		/// </summary>
		VarValueNode(char var);

		/// <summary>
		/// Gets the value as a string
		/// </summary>
		/// <returns>The node as a string</returns>
		string Print(const IPrinter& printer) const override;

		/// <summary>
		/// Checks if node can be represented as a double
		/// </summary>
		/// <returns>true if node can be represented as a double</returns>
		bool IsNumericalValue() const;
		
		/// <summary>
		/// Gets this as a double, if possible
		/// </summary>
		/// <returns>this node as a double value or NAN if not possible</returns>
		double AsDouble() const;

		/// <summary>
		/// Gets a clone of this
		/// </summary>
		unique_ptr<ExpNode> Clone() const;

	private:
		char variable_;
};