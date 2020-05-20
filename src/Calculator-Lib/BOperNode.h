#pragma once

#include <memory>
#include <string>
#include <vector>

#include "ExpNode.h"
#include "OperNode.h"

using namespace std;

class BOperNode : public OperNode {
	public:
		/// <summary>
		/// Copy constructor
		/// </summary>
		BOperNode(const BOperNode &other);

		/// <summary>
		/// Creates a BOperNode based on the operator's character
		/// </summary>
		/// <param name="c">Character operator</param>
		BOperNode(char c);

		/// <summary>
		/// Creates a BOperNode of operator
		/// </summary>
		/// <param name="oper">operator</param>
		BOperNode(Operator oper);

		/// <summary>
		/// Adds node as a child and set node's parent to this
		/// </summary>
		/// <param name="node">New child node</param>
		void AddChild(unique_ptr<ExpNode> node) override;

		/// <summary>
		/// Inserts child between this and its last child
		/// </summary>
		/// <param name="node">this's new child node</param>
		void InsertChild(unique_ptr<OperNode> node) override;

		/// <summary>
		/// Gets child at index
		/// </summary>
		/// <returns>child at index</returns>
		const ExpNode &GetChild(int index) const override;

		/// <summary>
		/// Gets amount of children
		/// </summary>
		/// <returns>children count</returns>
		int ChildCount() const override;
		
		/// <summary>
		/// Copies and simplifies ExpNode and descendents
		/// </summary>
		/// <returns>A simplified expression of this</returns>
		unique_ptr<ExpNode> Simplify() const override;

		/// <summary>
		/// Gets the expression tree printed from this down
		/// </summary>
		/// <returns>The expression tree as a string</returns>
		string Print(const IPrinter& printer) const override;

		/// <summary>
		/// Gets a clone of this
		/// </summary>
		unique_ptr<ExpNode> Clone() const override;
	private:
		unique_ptr<ExpNode> left_child;
		unique_ptr<ExpNode> right_child;
};
