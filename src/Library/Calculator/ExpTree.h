#pragma once

#include <memory>
#include <string>

#include "IOperation.h"

#include "ExpNode.h"
#include "FValueNode.h"
#include "IValueNode.h"
#include "OperNode.h"
#include "ValueNode.h"

using namespace std;

class ExpTree {
	public:
		ExpTree();

		/// <summary>
		/// Adds an OperNode to the tree
		/// </summary>
		/// <param name="node">OperNode to add to tree</pararm>
		void AddNode(unique_ptr<BranchNode> node);

		/// <summary>
		/// Adds a ValueNode to the tree
		/// </summary>
		/// <param name="node">ValueNode to add to tree</pararm>
		void AddNode(unique_ptr<ValueNode> node);

		/// <summary>
		/// Adds an ExoNode to the tree
		/// </summary>
		/// <param name="node">ExpNode to add to tree</pararm>
		void AddAnyNode(unique_ptr<ExpNode> node);

		/// <summary>
		/// Finds the closest UNRESOLVED_PARENTHESIS and change it to PARENTHESIS. 
		/// Then, set that node as active_node
		/// </summary>
		void CloseParenthesis();

		/// <summary>
		/// Executes operation on ExpNodes and returns root node
		/// </summary>
		/// <returns>New root node</returns>
		unique_ptr<ExpNode> Execute(IOperation* operation) const;

		/// <summary>
		/// Gets the root node
		/// </summary>
		/// <returns>root_node</returns>
		unique_ptr<ExpNode> GetRoot();

		string Print(const IPrinter& printer) const;

	private:
		/// <summary>
		/// Adds an OperNode to the tree.
		/// </summary>
		/// <param name="node">The oper node to add</param>
		void AddOperNode(unique_ptr<BranchNode> node);

		/// <summary>
		/// Finds insertion point for node and changes active_node to it
		/// </summary>
		/// <param name="node">Node to insert</param>
		void FindInsertionNode(const ExpNode &node);

		/// <summary>
		/// Inserts an OperNode differently depending on it's oper type
		/// </summary>
		void InsertOperNode(unique_ptr<BranchNode> node);

		// Tracks the last insertion point during parsing.
		BranchNode *active_node;

		unique_ptr<ExpNode> root_node;
};
