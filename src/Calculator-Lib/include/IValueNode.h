#pragma once

#include "ExpNode.h"
#include "ValueNode.h"

class IValueNode : public ValueNode {
	public:
		/// <summary>
		/// Creates a ValueNode with i_value value
		/// </summary>
		/// <param name="value">initial value for node</param>
		IValueNode(int value);

		/// <summary>
		/// Gets the int value
		/// </summary>
		/// <returns>i_value</returns>
		int GetValue() const;

		/// <summary>
		/// Sets the int value
		/// </summary>
		/// <param name="value">New value for IValueNode</param>
		void SetValue(int value);

		/// <summary>
		/// Checks if node can be represented as a double
		/// </summary>
		/// <returns>true if node can be represented as a double</returns>
		bool IsNumericalValue() const override;

		/// <summary>
		/// Gets this as a double, if possible
		/// </summary>
		/// <returns>this node as a double value or NAN if not possible</returns>
		double AsDouble() const override;

		/// <summary>
		/// Gets the value as a string
		/// </summary>
		/// <returns>The node as a string</returns>
		string Print() const override;

		/// <summary>
		/// Gets a clone of this
		/// </summary>
		unique_ptr<ExpNode> Clone() const override;

	private:
		int i_value;
};
