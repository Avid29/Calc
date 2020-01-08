#pragma once

#include "ExpNode.h"
#include "ValueNode.h"

class FValueNode : public ValueNode {
	public:
		/// <summary>
		/// Create a ValueNode with f_value value
		/// </summary>
		/// <param name="value">initial value for node</param>
		FValueNode(double value);

		/// <summary>
		/// Get the float value as a double
		/// </summary>
		/// <returns>f_value</returns>
		double GetValue();

		/// <summary>
		/// Set the float value
		/// </summary>
		/// <param name="value">New value for FValueNode</param>
		void SetValue(double value);

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
		double f_value;
};
