#pragma once

#include <string>
#include <memory>

#include "ExpNode.h"

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
	PARENTHESIS // Closed Parenthesis
};

class OperNode : public ExpNode {
	public:
		/// <summary>
		/// Adds child and set its parent
		/// </summary>
		/// <param name="node">New child node</param>
		virtual void AddChild(unique_ptr<ExpNode> node) = 0;

		/// <summary>
		/// Inserts child between this and its last child
		/// </summary>
		/// <param name="node">this's new child node</param>
		virtual void InsertChild(unique_ptr<OperNode> node) = 0;

		/// <summary>
		/// Gets child at index
		/// </summary>
		/// <returns>child at index</returns>
		virtual const ExpNode& GetChild(int index) const = 0;

		/// <summary>
		/// Gets amount of children
		/// </summary>
		/// <returns>children count</returns>
		virtual int ChildCount() const = 0;

		/// <summary>
		/// Checks if node can be represented as a double
		/// </summary>
		/// <returns>true if node can be represented as a double</returns>
		bool IsNumericalValue() const;

		/// <summary>
		/// Checks if node is a value
		/// </summary>
		/// <returns>true if node is a value</returns>
		bool IsValue() const;
		
		/// <summary>
		/// Gets this as a double, if possible
		/// </summary>
		/// <returns>this node as a double value or NAN if not possible</returns>
		double AsDouble() const;

		virtual unique_ptr<ExpNode> Simplify() const = 0;

		virtual string Print() const = 0;

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

		/// <summary>
		/// Gets a clone of this
		/// </summary>
		virtual unique_ptr<ExpNode> Clone() const = 0;
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