#pragma once

#include <string>
#include <memory>

#include "BranchNode.h"

using namespace std;

enum class Operator {
	ADDITION,
	MULTIPLICATION,
	POWER,
	POSITIVE,
	NEGATIVE,
	RECIPROCAL,
	SINE,
	COSINE,
	TANGENT,
	COSECANT,
	SECANT,
	COTANGENT,
	DERIVATIVE,
	UNRESOLVED_PARENTHESIS, // Parenthesis
	PARENTHESIS, // Closed Parenthesis
	Vector,
};

class OperNode : public BranchNode {
	public:
		/// <summary>
		/// Gets the priority based on the oper
		/// </summary>
		/// <returns>Proirity value</returns>
		Priority GetPriority() const override;

		/// <summary>
		/// Gets the OperNode's Operator
		/// </summary>
		/// <returns>oper_</returns>
		Operator GetOperator() const;

		bool IsOperNode() const override;

		const OperNode* AsOperNode() const override;

	protected:
		Operator oper_;	
};

/// <summary>
/// Checks if an operator is Unary
/// </summary>
/// <param name="oper">Operator to check for Unary type</param>
/// <returns>true if oper is a Unary operator</returns>
bool IsUnary(Operator oper);

/// <summary>
/// Checks if an operator is Binary
/// </summary>
/// <param name="oper">Operator to check for Nary type</param>
/// <returns>true if oper is a Binary operator</returns>
bool IsBinary(Operator oper);

/// <summary>
/// Checks if an operator is Nary
/// </summary>
/// <param name="oper">Operator to check for Nary type</param>
/// <returns>true if oper is an Nary operator</returns>
bool IsNary(Operator oper);