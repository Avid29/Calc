#include <string>
#include <vector>

#include "../include/ExpNode.h"
#include "../include/OperNode.h"

using namespace std;

/// <summary>
/// Get the priority based on the oper
/// </summary>
/// <returns>Proirity value</returns>
Priority OperNode::GetPriority() {
	switch (oper_) {
		case ADDITION_OPER:
			return Priority::ADDITION;
		case MULTIPLICATION_OPER:
			return Priority::MULTIPLICATION;
		case POWER_OPER:
			return Priority::POWER;
		case OVERRIDE_OPER:
			return Priority::OVERRIDE;
			
			// VALUE has locked children, this prevents the OVERRIDE special case
		case OVERRIDEN_OPER:
			return Priority::VALUE;
	}
	return VALUE;
}

/// <summary>
/// Get the OperNode's Operator
/// </summary>
/// <returns>oper_</returns>
Operator OperNode::GetOperator() {
	return oper_;
}

/// <summary>
/// Check if an operator is Unary
/// </summary>
/// <param name="oper">Operator to check for Unary type</param>
/// <returns>True if oper is a Unary operator</returns>
bool IsUnary(Operator oper) {
	return oper == POSITIVE_OPER || oper == NEGATIVE_OPER ||
		oper == OVERRIDE_OPER || oper == OVERRIDEN_OPER;
}

/// <summary>
/// Check if an operator is Nary
/// </summary>
/// <param name="oper">Operator to check for Nary type</param>
/// <returns>True if oper is a Nary operator</returns>
bool IsNary(Operator oper) {
	return oper == ADDITION_OPER || oper == MULTIPLICATION_OPER;
}