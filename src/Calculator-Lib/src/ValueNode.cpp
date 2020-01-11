#include "../include/FValueNode.h"
#include "../include/IValueNode.h"
#include "../include/ValueNode.h"

/// <summary>
/// Simplifies ExpNode and children
/// </summary>
/// <returns>The new simplest node possible in place of this</returns>
ExpNode* ValueNode::Simplify() {
	return this;
}

/// <summary>
/// The Priority of a value is always VALUE
/// </summary>
/// <returns>VALUE</returns>
Priority ValueNode::GetPriority()
{
	return Priority::VALUE;
}

/// <summary>
/// Checks if node is a value
/// </summary>
/// <returns>true if node is a value</returns>
bool ValueNode::IsValue() {
	return true;
}

/// <summary>
/// Gets most appropiate ValueNodeType
/// </summary>
/// <returns>ValueNode of Value and simplest node type</returns>
ValueNode *GetValueNode(double value) {
	if (floor(value) == value) {
		return new IValueNode((int)value);
	}
	else {
		return new FValueNode(value);
	}
}