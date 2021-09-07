#include "SinusoidalOperNode.h"

/// <summary>
/// Copy constructor
/// </summary>
SinusoidalOperNode::SinusoidalOperNode(const SinusoidalOperNode& other) : UOperNode(other) { }

/// <summary>
/// Creates a UOperNode of operator
/// </summary>
/// <param name="oper">operator</param>
SinusoidalOperNode::SinusoidalOperNode(Operator oper) : UOperNode(oper) {
	oper_ = oper;
}

/// <summary>
/// Simplifies ExpNode and children
/// </summary>
/// <returns>The new simplest node possible in place of this</returns>
unique_ptr<ExpNode> SinusoidalOperNode::Execute(IOperation* operation) const {
	return operation->Execute(*this);
}

/// <summary>
/// Get the expression tree printed from this down
/// </summary>
/// <returns>The expression tree as a string</returns>
string SinusoidalOperNode::Print(const IPrinter& printer) const {
	return printer.Print(*this);
}

/// <summary>
/// Gets a clone of this
/// </summary>
unique_ptr<ExpNode> SinusoidalOperNode::Clone() const {
	return make_unique<SinusoidalOperNode>(*this);
}
