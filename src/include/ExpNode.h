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
		/// Sets node as the parent of this
		/// </summary>
		/// <param name="node">New parent node</param>
		void SetParent(OperNode* node);

		/// <summary>
		/// Sets node as the parent of this and this as the child of node
		/// </summary>
		/// <param name="node">New parent node</param>
		void InsertAbove(OperNode *node);

		/// <summary>
		/// Gets this node's parent
		/// </summary>
		/// <returns>parent_</returns>
		OperNode *GetParent();

		virtual bool IsNumericalValue() = 0;

		virtual double AsDouble() = 0;

		virtual ExpNode* Simplify() = 0;

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
