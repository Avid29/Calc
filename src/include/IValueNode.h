#pragma once

#include "ExpNode.h"
#include "ValueNode.h"

class IValueNode : public ValueNode {
	public:
		/// <summary>
		/// Create a ValueNode with f_value value
		/// </summary>
		/// <param name="value">initial value for node</param>
		IValueNode(int value);

		/// <summary>
		/// Get the int value
		/// </summary>
		/// <returns>i_value</returns>
		int GetValue();

		/// <summary>
		/// Set the int value
		/// </summary>
		/// <param name="value">New value for IValueNode</param>
		void SetValue(int value);

		/// <summary>
		/// Gets this as a double, if possible
		/// </summary>
		/// <returns>this node as a double value or NAN if not possible</returns>
		double AsDouble();

		/// <summary>
		/// Get the value as a string
		/// </summary>
		/// <returns>The node as a string</returns>
		string Print();

		/// <summary>
		/// The Priority of an float value is always VALUE
		/// </summary>
		/// <returns>VALUE</returns>
		Priority GetPriority();

	private:
		int i_value;
};
