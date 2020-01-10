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
		string Print();

		/// <summary>
		/// Checks if node can be represented as a double
		/// </summary>
		/// <returns>true if node can be represented as a double</returns>
		bool IsNumericalValue();
		
		/// <summary>
		/// Gets this as a double, if possible
		/// </summary>
		/// <returns>this node as a double value or NAN if not possible</returns>
		double AsDouble();

	private:
		char variable_;
};