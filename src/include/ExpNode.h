#pragma once

#include <string>
#include <memory>
#include <vector>

using namespace std;

// Higher values go higher on the tree
enum class Priority {
	OVERRIDE = -1, // Parenthesis
	VALUE,
	UNARY,
	POWER,
	MULTIPLICATION,
	ADDITION
};

class OperNode;
class ValueNode;

class ExpNode {
	public:
		ExpNode();

		/// <summary>
		/// Set <see cref="node"/> as the parent of <see cref="this"/>
		/// </summary>
		/// <param name="node">New parent node</param>
		void SetParent(OperNode* node);

		/// <summary>
		/// Set node as the parent of this and this as the child of node
		/// </summary>
		/// <param name="node">New parent node</param>
		void InsertAbove(OperNode *node);

		/// <summary>
		/// Get parent_
		/// </summary>
		/// <returns>parent_</returns>
		OperNode *GetParent();

		/// <summary>
		/// Get the expression tree printed from this down
		/// </summary>
		/// <returns>The expression tree as a string</returns>
		virtual string Print() = 0;

		virtual Priority GetPriority() = 0;

		/// <summary>
		/// Checks if this has parent (if it does not, it's the root node
		/// </summary>
		/// <returns>true if this is the root node</returns>
		bool IsRoot();
	protected:
		OperNode *parent_;
};
