#include <string>
#include <vector>

#include "../include/ExpNode.h"
#include "../include/OperNode.h"

using namespace std;

/// <summary>
/// Checks if node can be represented as a double
/// </summary>
/// <returns>true if node can be represented as a double</returns>
bool OperNode::IsNumericalValue() {
	return false;
}

/// <summary>
/// Checks if node is a value
/// </summary>
/// <returns>true if node is a value</returns>
bool OperNode::IsValue() {
	return false;
}

/// <summary>
/// Gets this as a double, if possible
/// </summary>
/// <returns>this node as a double value or NAN if not possible</returns>
double OperNode::AsDouble() {
	return NAN;
}

/// <summary>
/// Gets the priority based on the oper
/// </summary>
/// <returns>Proirity value</returns>
Priority OperNode::GetPriority() {
	switch (oper_) {
		case Operator::ADDITION:
			return Priority::ADDITION;
		case Operator::MULTIPLICATION:
			return Priority::MULTIPLICATION;
		case Operator::POWER:
			return Priority::POWER;
		case Operator::UNRESOLVED_PARENTHESIS:
			return Priority::OVERRIDE;
			
			// VALUE has locked children, this prevents the OVERRIDE special case
		case Operator::PARENTHESIS:
			return Priority::VALUE;
	}
	return Priority::VALUE;
}

/// <summary>
/// Gets the OperNode's Operator
/// </summary>
/// <returns>oper_</returns>
Operator OperNode::GetOperator() {
	return oper_;
}

/// <summary>
/// Checks if an operator is Unary
/// </summary>
/// <param name="oper">Operator to check for Unary type</param>
/// <returns>true if oper is a Unary operator</returns>
bool IsUnary(Operator oper) {
	return oper == Operator::POSITIVE ||
		oper == Operator::NEGATIVE ||
		oper == Operator::UNRESOLVED_PARENTHESIS ||
		oper == Operator::PARENTHESIS;
}

/// <summary>
/// Checks if an operator is Binary
/// </summary>
/// <param name="oper">Operator to check for Nary type</param>
/// <returns>true if oper is a Binary operator</returns>
bool IsBinary(Operator oper) {
	return oper == Operator::POWER;
}

/// <summary>
/// Checks if an operator is Nary
/// </summary>
/// <param name="oper">Operator to check for Nary type</param>
/// <returns>true if oper is a Nary operator</returns>
bool IsNary(Operator oper) {
	return oper == Operator::ADDITION ||
		oper == Operator::MULTIPLICATION;
}