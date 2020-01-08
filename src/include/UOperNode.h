#pragma once

#include <string>
#include <vector>

#include "ExpNode.h"
#include "OperNode.h"

using namespace std;

class UOperNode : OperNode {
	public:
		// <summary>
		/// Set child of operator
		/// </summary>
		/// <param name="node">New child node</param>
		virtual void AddChild(::ExpNode *node);

		/// <summary>
		/// Get the expression tree printed from this down
		/// </summary>
		/// <returns>The expression tree as a string</returns>
		string Print();

	protected:
		::ExpNode *child_;
};
