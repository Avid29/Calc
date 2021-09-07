#pragma once

#include <string>
#include <vector>

#include "ExpNode.h"
#include "OperNode.h"

using namespace std;

class UOperNode : public OperNode {
	public:
		/// <summary>
		/// Copy constructor
		/// </summary>
		UOperNode(const UOperNode &other);

		/// <summary>
		/// Create a UOperNode based on the operator's character
		/// </summary>
		/// <param name="c">Character operator</param>
		UOperNode(char c);

		/// <summary>
		/// Create a UOperNode of operator
		/// </summary>
		/// <param name="oper">operator</param>
		UOperNode(Operator oper);

		/// <summary>
		/// Set child of operator
		/// </summary>
		/// <param name="node">New child node</param>
		void AddChild(unique_ptr<ExpNode> node) override;

		/// <summary>
		/// Set child of operator
		/// </summary>
		/// <param name="node">New child node</param>
		/// <param name="overwrite">Overwrite current child if existant</param>
		void AddChild(unique_ptr<ExpNode> node, bool overwrite);

		/// <summary>
		/// Insert child between this and its child
		/// </summary>
		/// <param name="node">this's new child node</param>
		void InsertChild(unique_ptr<BranchNode> node) override;

		/// <summary>
		/// Gets child at index
		/// </summary>
		/// <returns>child at index</returns>
		const ExpNode &GetChild(int index) const override;

		/// <summary>
		/// Gets amount of children
		/// </summary>
		/// <returns>children count</returns>
		int ChildCount() const;

		void ClearChildren();

		/// <summary>
		/// Check if UOperNode's child_ is set
		/// </summary>
		/// <returns>true if child_ is not null</returns>
		bool HasChild();

		/// <summary>
		/// Changes priority from OVERRIDE to VALUE when OVERRIDE finished
		/// </summary>
		void RemoveOverride();

		bool IsConstant() const override;

		bool IsConstantBy(const VarValueNode& node) const override;

		/// <summary>
		/// Simplifies ExpNode and children
		/// </summary>
		/// <returns>The new simplest node possible in place of this</returns>
		unique_ptr<ExpNode> Execute(IOperation* operation) const override;

		/// <summary>
		/// Get the expression tree printed from this down
		/// </summary>
		/// <returns>The expression tree as a string</returns>
		string Print(const IPrinter& printer) const override;

		/// <summary>
		/// Gets a clone of this
		/// </summary>
		unique_ptr<ExpNode> Clone() const override;

	protected:
		unique_ptr<ExpNode> child_;
};

/// <summary>
/// Checks if the operation is a suffix or prefix
/// </summary>
bool IsSuffix(Operator oper);