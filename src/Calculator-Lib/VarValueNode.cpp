#include "ValueNode.h"
#include "VarValueNode.h"


/// <summary>
/// Creates a VarValueNode with variable var
/// </summary>
VarValueNode::VarValueNode(char var) : variable_ (var) {}

/// <summary>
/// Gets the value as a string
/// </summary>
/// <returns>The node as a string</returns>
string VarValueNode::Print(const IPrinter& printer) const {
	return printer.Print(*this);
}

char VarValueNode::GetCharacter() const {
	return variable_;
}

/// <summary>
/// Checks if node can be represented as a double
/// </summary>
/// <returns>true if node can be represented as a double</returns>
bool VarValueNode::IsNumericalValue() const {
	return false;
}

/// <summary>
/// Gets this as a double, if possible
/// </summary>
/// <returns>this node as a double value or NAN if not possible</returns>
double VarValueNode::AsDouble() const {
	return NAN;
}

bool VarValueNode::IsConstant() const {
	return false;
}

bool VarValueNode::IsConstantBy(const VarValueNode& node) const {
	return node.GetCharacter() != this->GetCharacter();
}

/// <summary>
/// Simplifies ExpNode and children
/// </summary>
/// <returns>The new simplest node possible in place of this</returns>
unique_ptr<ExpNode> VarValueNode::Execute(IOperation* operation) const {
	return operation->Execute(*this);
}

/// <summary>
/// Gets a clone of this
/// </summary>
unique_ptr<ExpNode> VarValueNode::Clone() const {
	return make_unique<VarValueNode>(*this);
}