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
		/// <param name="node">Character operator</param>
		NOperNode(char c);

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
		/// Get the expression tree printed from this down
		/// </summary>
		/// <returns>The expression tree as a string</returns>
		string Print();
	protected:
		vector<::ExpNode*> children_;
};
