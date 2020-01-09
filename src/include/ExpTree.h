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
		/// Find the closest OVERRIDE and change it to OVERRIDEN. 
		/// Then, set OVERRIDE as active_node
		/// </summary>
		void FinishOverride();

		string Print(); 

	private:
		OperNode *active_node;

		// The first node is often a value node.
		//This has to be handled seperatly to avoid unsafe casting
		ValueNode* init_value_node;


		// TODO: Better memory management: unique_ptr<ExpNode> root_node;
};
