#include <string>

#include "ExpNode.h"
#include "FValueNode.h"
#include "IValueNode.h"
#include "ValueNode.h"

using namespace std;

/// <summary>
/// Creates a ValueNode with f_value value
/// </summary>
/// <param name="value">initial value for node</param>
IValueNode::IValueNode(int value) : i_value (value) {}

/// <summary>
/// Gets the int value
/// </summary>
/// <returns>i_value</returns>
int IValueNode::GetValue() const {
	return i_value;
}

/// <summary>
/// Sets the int value
/// </summary>
/// <param name="value">New value for IValueNode</param>
void IValueNode::SetValue(int value) {
	i_value = value;
}

/// <summary>
/// Checks if node can be represented as a double
/// </summary>
/// <returns>true if node can be represented as a double</return>
bool IValueNode::IsNumericalValue() const {
	return true;
}

/// <summary>
/// Gets this as a double, if possible
/// </summary>
/// <returns>this node as a double value or NAN if not possible</returns>
double IValueNode::AsDouble() const {
	return (double)GetValue();
}

/// <summary>
/// Simplifies ExpNode and children
/// </summary>
/// <returns>The new simplest node possible in place of this</returns>
unique_ptr<ExpNode> IValueNode::Execute(IOperation* operation) const {
	return operation->Execute(*this);
}

/// <summary>
/// Gets the value as a string
/// </summary>
/// <returns>The node as a string</returns>
string IValueNode::Print(const IPrinter& printer) const {
	return printer.Print(*this);
}

/// <summary>
/// Gets a clone of this
/// </summary>
unique_ptr<ExpNode> IValueNode::Clone() const {
	return make_unique<IValueNode>(*this);
}