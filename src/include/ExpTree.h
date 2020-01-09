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
		/// Add an OperNode to the tree
		/// </summary>
		/// <param name="node">OperNode to add to tree</pararm>
		void AddNode(OperNode *node);

		/// <summary>
		/// Add an ValueNode to the tree
		/// </summary>
		/// <param name="node">ValueNode to add to tree</pararm>
		void AddNode(ValueNode *node);

		/// <summary>
		/// Finds the closest UNRESOLVED_PARENTHESIS and change it to PARENTHESIS. 
		/// Then, set that node as active_node
		/// </summary>
		void CloseParenthesis();


		string Print(); 

	private:
		/// <summary>
		/// Finds insertion point for node and changes active_node to it
		/// </summary>
		/// <param name="node">Node to insert</param>
		void FindInsertionNode(ExpNode *node);

		/// <summary>
		/// Inserts an OperNode differently depending on it's oper type
		/// </summary>
		void InsertOperNode(OperNode *node);

		OperNode *active_node;

		// The first node is often a value node.
		//This has to be handled seperatly to avoid unsafe casting
		ValueNode* init_value_node;


		// TODO: Better memory management: unique_ptr<ExpNode> root_node;
};
