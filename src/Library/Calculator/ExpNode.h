#pragma once

#include <string>
#include <memory>
#include <vector>

#include "IOperation.h"
#include "IPrinter.h"

using namespace std;

// Higher values go higher on the tree
// Order of operations
enum class Priority {
	OVERRIDE = -1, // Parenthesis or Collections
	VALUE,
	UNARY,
	POWER,
	MULTIPLICATION,
	ADDITION,
	EQUALS
};

class BranchNode;

class ExpNode {
	public:
		ExpNode();

		virtual ~ExpNode() = default;

		/// <summary>
		/// Sets node as the parent of this
		/// </summary>
		/// <param name="node">New parent node</param>
		void SetParent(BranchNode *node);

		/// <summary>
		/// Gets this node's parent
		/// </summary>
		/// <returns>parent_</returns>
		BranchNode *GetParent() const;

		virtual bool IsNumericalValue() const = 0;

		virtual bool IsValue() const = 0;

		virtual bool IsConstant() const = 0;

		virtual bool IsConstantBy(const VarValueNode& node) const = 0;

		virtual double AsDouble() const = 0;

		virtual unique_ptr<ExpNode> Execute(IOperation* operation) const = 0;

		virtual string Print(const IPrinter& printer) const = 0;

		/// <summary>
		/// Gets the priority of the node by operation or type
		/// </summary>
		/// <returns>The priority of depth on the tree</returns>
		virtual Priority GetPriority() const = 0;

		/// <summary>
		/// Checks if this has parent (if it does not, it's the root node)
		/// </summary>
		/// <returns>true if this is the root node</returns>
		bool IsRoot();

		/// <summary>
		/// Gets a clone of this
		/// </summary>
		virtual unique_ptr<ExpNode> Clone() const = 0;
	protected:
		BranchNode *parent_ = nullptr;
};
