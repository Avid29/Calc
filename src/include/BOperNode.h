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
		/// Creates a BOperNode based on the operator's character
		/// </summary>
		/// <param name="node">Character operator</param>
		BOperNode(char c);

		/// <summary>
		/// Add node as a child and set node's parent to this
		/// </summary>
		/// <param name="node">New child node</param>
		virtual void AddChild(::ExpNode *node);

		/// <summary>
		/// Inserts child between this and its last child
		/// </summary>
		/// <param name="node">this's new child node</param>
		virtual void InsertChild(OperNode* node);

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
	protected:
		::ExpNode *left_child;
		::ExpNode *right_child;
};
