#include "FValueNode.h"
#include "IValueNode.h"
#include "ValueNode.h"

using namespace std;

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

bool ValueNode::IsConstant() const {
	// VarValueNode overwrites
	return true;
}

bool ValueNode::IsConstantBy(const VarValueNode& node) const {
	// VarValueNode overwrites
	return true;
}