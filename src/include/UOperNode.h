#pragma once

#include <string>
#include <vector>

#include "ExpNode.h"
#include "OperNode.h"

using namespace std;

class UOperNode : public OperNode {
	public:
		/// <summary>
		/// Create a UOperNode based on the operator's character
		/// </summary>
		/// <param name="node">Character operator</param>
		UOperNode(char c);

		/// <summary>
		/// Set child of operator
		/// </summary>
		/// <param name="node">New child node</param>
		virtual void AddChild(::ExpNode *node);

		/// <summary>
		/// Set child of operator
		/// </summary>
		/// <param name="node">New child node</param>
		/// <param name="overwrite">Overwrite current child if existant</param>
		virtual void AddChild(::ExpNode *node, bool overwrite);

		/// <summary>
		/// Insert child between this and its child
		/// </summary>
		/// <param name="node">this's new child node</param>
		void InsertChild(::OperNode* node);

		/// <summary>
		/// Replaces a child with a different ExpNode
		// </summary>
		virtual void ReplaceChild(ExpNode* newNode, ExpNode* oldNode);

		/// <summary>
		/// Check if UOperNode's child_ is set
		/// </summary>
		/// <returns>true if child_ is not null</returns>
		bool HasChild();

		/// <summary>
		/// Changes priority from OVERRIDE to VALUE when OVERRIDE finished
		/// </summary>
		void RemoveOverride();

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
		::ExpNode *child_;
};
