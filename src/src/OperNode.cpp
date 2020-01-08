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
		case ADDITION:
				return ADD;
		case MULTIPLICATION:
				return MULT;
		case POWER:
				return POW;
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
	return oper == ADDITION || oper == MULTIPLICATION;
}