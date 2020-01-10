#include <sstream>
#include <string>

#include "../include/ExpNode.h"
#include "../include/FValueNode.h"
#include "../include/IValueNode.h"
#include "../include/ValueNode.h"

using namespace std;

/// <summary>
/// Creates a ValueNode with f_value value
/// </summary>
/// <param name="value">initial value for node</param>
FValueNode::FValueNode(double value) : f_value (value) {}

/// <summary>
/// Gets the float value as a double
/// </summary>
/// <returns>f_value</returns>
double FValueNode::GetValue() {
	return f_value;
}

/// <summary>
/// Sets the float value
/// </summary>
/// <param name="value">New value for FValueNode</param>
void FValueNode::SetValue(double value) {
	f_value = value;
}

/// <summary>
/// Checks if node can be represented as a double
/// </summary>
/// <returns>true if node can be represented as a double</returns>
bool FValueNode::IsNumericalValue() {
	return true;
}

/// <summary>
/// Gets this as a double, if possible
/// </summary>
/// <returns>this node as a double value or NAN if not possible</returns>
double FValueNode::AsDouble() {
	return GetValue();
}

/// <summary>
/// Gets the value as a string
/// </summary>
/// <returns>The node as a string</returns>
string FValueNode::Print() {
	ostringstream oss;
	oss << f_value;
	return oss.str();
}