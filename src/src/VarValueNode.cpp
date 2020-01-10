

#include "../include/ValueNode.h"
#include "../include/VarValueNode.h"


/// <summary>
/// Creates a VarValueNode with variable var
/// </summary>
VarValueNode::VarValueNode(char var) : variable_ (var) {}

/// <summary>
/// Gets the value as a string
/// </summary>
/// <returns>The node as a string</returns>
string VarValueNode::Print() {
	return string(1, variable_);
}

/// <summary>
/// Checks if node can be represented as a double
/// </summary>
/// <returns>true if node can be represented as a double</returns>
bool VarValueNode::IsNumericalValue() {
	return false;
}

/// <summary>
/// Gets this as a double, if possible
/// </summary>
/// <returns>this node as a double value or NAN if not possible</returns>
double VarValueNode::AsDouble() {
	return NAN;
}