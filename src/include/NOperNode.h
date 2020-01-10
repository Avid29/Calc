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
		/// Create an NOperNode based on the operator's character
		/// </summary>
		/// <param name="c">Character operator</param>
		NOperNode(char c);

		/// <summary>
		/// Create an NOperNode by operator
		/// </summary>
		/// <param name="oper">operator</param>
		NOperNode(Operator oper);

		/// <summary>
		/// Add child and set its parent
		/// </summary>
		/// <param name="node">New child node</param>
		void AddChild(::ExpNode *node);

		/// <summary>
		/// Insert child between this and its last child
		/// </summary>
		/// <param name="node">this's new child node</param>
		void InsertChild(::OperNode *node);

		/// <summary>
		/// Replaces a child with a different ExpNode
		// </summary>
		virtual void ReplaceChild(ExpNode* newNode, ExpNode* oldNode);

		/// <summary>
		/// Simplifies ExpNode and children
		/// </summary>
		/// <returns>The new simplest node possible in place of this</returns>
		ExpNode* Simplify();

		/// <summary>
		/// Get the expression tree printed from this down
		/// </summary>
		/// <returns>The expression tree as a string</returns>
		string Print();
	private:
		vector<::ExpNode*> children_;
};
