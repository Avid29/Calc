#pragma once

#include <string>
#include <memory>

#include "ExpNode.h"

using namespace std;

enum Operator {
	ADDITION,
	MULTIPLICATION,
	POWER,
	POS,
	NEG
};

class OperNode : public ExpNode {
	public:
		/// <summary>
		/// Add child and set its parent
		/// </summary>
		/// <param name="node">New child node</param>
		virtual void AddChild(ExpNode *node) = 0;

		// <summary>
		/// Insert child between this and its last child
		/// </summary>
		/// <param name="node">this's new child node</param>
		virtual void InsertChild(OperNode *node) = 0;

		virtual string Print() = 0;

		/// <summary>
		/// Get the priority based on the oper
		/// </summary>
		/// <returns>Proirity value</returns>
		Priority GetPriority();

		/// <summary>
		/// Get the OperNode's Operator
		/// </summary>
		/// <returns>oper_</returns>
		Operator GetOperator();

	protected:
		Operator oper_;	
};

/// <summary>
/// Check if an operator is Unary
/// </summary>
/// <param name="oper">Operator to check for Unary type</param>
/// <returns>True if oper is a Unary operator</returns>
bool IsUnary(Operator oper);