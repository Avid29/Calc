#pragma once

#include <memory>
#include <string>

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
		void AddNode(unique_ptr<OperNode> node);

		/// <summary>
		/// Adds an ValueNode to the tree
		/// </summary>
		/// <param name="node">ValueNode to add to tree</pararm>
		void AddNode(unique_ptr<ValueNode> node);

		/// <summary>
		/// Finds the closest UNRESOLVED_PARENTHESIS and change it to PARENTHESIS. 
		/// Then, set that node as active_node
		/// </summary>
		void CloseParenthesis();

		/// <summary>
		/// Simplifies ExpNodes and returns root node
		/// </summary>
		/// <returns>New root node</returns>
		unique_ptr<ExpNode> Simplify() const;

		/// <summary>
		/// Simplifies ExpNode and children
		/// </summary>
		unique_ptr<ExpTree> SimplifyTree();

		string Print() const; 

	private:
		/// <summary>
		/// Finds insertion point for node and changes active_node to it
		/// </summary>
		/// <param name="node">Node to insert</param>
		void FindInsertionNode(const ExpNode &node);

		/// <summary>
		/// Inserts an OperNode differently depending on it's oper type
		/// </summary>
		void InsertOperNode(unique_ptr<OperNode> node);

		// Tracks the last insertion point during parsing.
		OperNode *active_node;

		unique_ptr<ExpNode> root_node;
};
