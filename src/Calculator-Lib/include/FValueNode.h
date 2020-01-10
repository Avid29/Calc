#pragma once

#include "ExpNode.h"
#include "ValueNode.h"

class FValueNode : public ValueNode {
	public:
		/// <summary>
		/// Creates a ValueNode with f_value value
		/// </summary>
		/// <param name="value">initial value for node</param>
		FValueNode(double value);

		/// <summary>
		/// Gets the float value as a double
		/// </summary>
		/// <returns>f_value</returns>
		double GetValue();

		/// <summary>
		/// Set the float value
		/// </summary>
		/// <param name="value">New value for FValueNode</param>
		void SetValue(double value);

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

		/// <summary>
		/// Gets the value as a string
		/// </summary>
		/// <returns>The node as a string</returns>
		string Print();

	private:
		double f_value;
};
