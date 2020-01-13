#pragma once

#include <memory>
#include <string>
#include <vector>

#include "ExpNode.h"
#include "OperNode.h"

using namespace std;

class NOperNode	: public OperNode {
	public:
		/// <summary>
		/// Copy constructor
		/// </summary>
		NOperNode(const NOperNode &other);

		/// <summary>
		/// Creates an NOperNode based on the operator's character
		/// </summary>
		/// <param name="c">Character operator</param>
		NOperNode(char c);

		/// <summary>
		/// Creates an NOperNode by operator
		/// </summary>
		/// <param name="oper">operator</param>
		NOperNode(Operator oper);

		/// <summary>
		/// Adds child and set its parent
		/// </summary>
		/// <param name="node">New child node</param>
		void AddChild(unique_ptr<ExpNode> node) override;

		/// <summary>
		/// Inserts child between this and its last child
		/// </summary>
		/// <param name="node">this's new child node</param>
		void InsertChild(unique_ptr<OperNode> node) override;

		/// <summary>
		/// Inserts child as a child at index
		/// </summary>
		void AddChildAt(unique_ptr<ExpNode> node, int index);

		/// <summary>
		/// Steals children from node
		/// </summary>
		/// <returns>coefficient</returns>
		double InheritChildren(NOperNode *node);

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
		/// Simplifies ExpNode and children
		/// </summary>
		/// <returns>The new simplest node possible in place of this</returns>
		unique_ptr<ExpNode> Simplify() const override;

		/// <summary>
		/// Check if node can inhert node from children and insert if possible
		/// </summary>
		/// <returns>-1 for failure</returns>
		double TryInheritChildren(ExpNode *node);

		/// <summary>
		/// Gets expanded version of node
		/// </summary>
		/// <returns> Expanded version of this</returns>
		unique_ptr<ExpNode> Expand();

		/// <summary>
		/// Gets the expression tree printed from this down
		/// </summary>
		/// <returns>The expression tree as a string</returns>
		string Print() const override;

		/// <summary>
		/// Gets a clone of this
		/// </summary>
		unique_ptr<ExpNode> Clone() const override;
	private:
		/// <summary>
		/// Sorts children into ATerms and applies properties to simplify them
		/// </summary>
		void SimplifyATerms();

		/// <summary>
		/// Sorts children into MTerms and applies properties to simplify them
		/// </summary>
		void SimplifyMTerms();

		vector<unique_ptr<ExpNode>> children_;
};
