
#include <string>
#include <vector>

#include "ExpNode.h"
#include "OperNode.h"

using namespace std;

/// <summary>
/// Gets the priority based on the oper
/// </summary>
/// <returns>Proirity value</returns>
Priority OperNode::GetPriority() const {
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
Operator OperNode::GetOperator() const {
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
		oper == Operator::RECIPROCAL ||
		oper == Operator::SINE ||
		oper == Operator::COSINE ||
		oper == Operator::TANGENT ||
		oper == Operator::COSECANT ||
		oper == Operator::SECANT ||
		oper == Operator::COTANGENT ||
		oper == Operator::DERIVATIVE ||
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