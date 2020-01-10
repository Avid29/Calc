# include "../include/ValueNode.h"

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
