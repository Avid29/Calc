#include <string>

#include "../include/ExpNode.h"
#include "../include/FValueNode.h"
#include "../include/IValueNode.h"
#include "../include/ValueNode.h"

using namespace std;

/// <summary>
/// Create a ValueNode with f_value value
/// </summary>
/// <param name="value">initial value for node</param>
FValueNode::FValueNode(double value) : f_value (value) {}

/// <summary>
/// Get the float value as a double
/// </summary>
/// <returns>f_value</returns>
double FValueNode::GetValue() {
	return f_value;
}

/// <summary>
/// Set the float value
/// </summary>
/// <param name="value">New value for FValueNode</param>
void FValueNode::SetValue(double value) {
	f_value = value;
}

/// <summary>
/// Get the value as a string
/// </summary>
/// <returns>The node as a string</returns>
string FValueNode::Print() {
	return to_string(f_value);
}

/// <summary>
/// The Priority of a float value is always VALUE
/// </summary>
/// <returns>VALUE</returns>
Priority FValueNode::GetPriority() {
	return Priority::VALUE;
}