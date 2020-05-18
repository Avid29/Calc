#include "FValueNode.h"
#include "IValueNode.h"
#include "ValueNode.h"

using namespace std;

/// <summary>
/// Simplifies ExpNode and children
/// </summary>
/// <returns>The new simplest node possible in place of this</returns>
unique_ptr<ExpNode> ValueNode::Simplify() const {
	return this->Clone();
}

/// <summary>
/// The Priority of a value is always VALUE
/// </summary>
/// <returns>VALUE</returns>
Priority ValueNode::GetPriority() const {
	return Priority::VALUE;
}

/// <summary>
/// Checks if node is a value
/// </summary>
/// <returns>true if node is a value</returns>
bool ValueNode::IsValue() const {
	return true;
}

/// <summary>
/// Gets most appropiate ValueNodeType
/// </summary>
/// <returns>ValueNode of Value and simplest node type</returns>
unique_ptr<ValueNode> MakeValueNode(double value) {
	if (floor(value) == value) {
		return make_unique<IValueNode>((int)value);
	}
	else {
		return make_unique<FValueNode>(value);
	}
}