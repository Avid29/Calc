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
IValueNode::IValueNode(int value) : i_value (value) {}

/// <summary>
/// Get the int value
/// </summary>
/// <returns>i_value</returns>
int IValueNode::GetValue() {
	return i_value;
}

/// <summary>
/// Set the int value
/// </summary>
/// <param name="value">New value for IValueNode</param>
void IValueNode::SetValue(int value) {
	i_value = value;
}

/// <summary>
/// Gets this as a double, if possible
/// </summary>
/// <returns>this node as a double value or NAN if not possible</returns>
double IValueNode::AsDouble() {
	return (double)GetValue();
}

/// <summary>
/// Get the value as a string
/// </summary>
/// <returns>The node as a string</returns>
string IValueNode::Print() {
	return to_string(i_value); 
}

/// <summary>
/// The Priority of an int value is always VALUE
/// </summary>
/// <returns>VALUE</returns>
Priority IValueNode::GetPriority() {
	return Priority::VALUE;
}