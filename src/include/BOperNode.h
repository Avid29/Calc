#pragma once

#include <memory>
#include <string>
#include <vector>

#include "ExpNode.h"
#include "OperNode.h"

using namespace std;

class BOperNode : OperNode {
	public:
		/// <summary>
		/// Add node as a child and set node's parent to this
		/// </summary>
		/// <param name="node">New child node</param>
		virtual void AddChild(::ExpNode *node);
		
		/// <summary>
		/// Get the expression tree printed from this down
		/// </summary>
		/// <returns>The expression tree as a string</returns>
		string Print();
	protected:
		::ExpNode *left_child;
		::ExpNode *right_child;
};
