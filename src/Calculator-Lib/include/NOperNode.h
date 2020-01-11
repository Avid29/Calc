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
		void AddChild(::ExpNode *node);

		/// <summary>
		/// Inserts child between this and its last child
		/// </summary>
		/// <param name="node">this's new child node</param>
		void InsertChild(::OperNode *node);

		/// <summary>
		/// Replaces a child with a different ExpNode
		// </summary>
		void ReplaceChild(ExpNode* newNode, ExpNode* oldNode);

		/// <summary>
		/// Steals children from node
		/// </summary>
		/// <returns>coefficient</returns>
		double InheritChildren(NOperNode *node);

		/// <summary>
		/// Gets child at index
		/// </summary>
		/// <returns>child at index</returns>
		ExpNode *GetChild(int index);

		/// <summary>
		/// Simplifies ExpNode and children
		/// </summary>
		/// <returns>The new simplest node possible in place of this</returns>
		ExpNode* Simplify();

		/// <summary>
		/// Gets the expression tree printed from this down
		/// </summary>
		/// <returns>The expression tree as a string</returns>
		string Print();
	private:
		/// <summary>
		/// Sorts children into ATerms and applies properties to simplify them
		/// </summary>
		void SimplifyATerms();

		/// <summary>
		/// Sorts children into MTerms and applies properties to simplify them
		/// </summary>
		void SimplifyMTerms();

		vector<::ExpNode*> children_;
};
