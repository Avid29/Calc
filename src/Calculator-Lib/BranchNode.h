#pragma once

#include "ExpNode.h"

class OperNode;

class BranchNode : public ExpNode
{
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
		virtual void InsertChild(unique_ptr<BranchNode> node) = 0;
	
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

		virtual void ClearChildren() = 0;

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

		/// <summary>
		/// Gets a clone of this
		/// </summary>
		virtual unique_ptr<ExpNode> Clone() const = 0;

		/// <summary>
		/// Gets the priority based on the oper
		/// </summary>
		/// <returns>Proirity value</returns>
		virtual Priority GetPriority() const = 0;
};
