#include <memory>

#include "../include/ExpNode.h"
#include "../include/ExpTree.h"
#include "../include/FValueNode.h"
#include "../include/IValueNode.h"
#include "../include/OperNode.h"
#include "../include/UOperNode.h"
#include "../include/ValueNode.h"

using namespace std;

ExpTree::ExpTree() : active_node (nullptr), init_value_node (nullptr)  {}

/// <summary>
/// Adds an OperNode to the tree
/// </summary>
/// <param name="node">OperNode to add to tree</param>
void ExpTree::AddNode(OperNode *node) {
	if (active_node == nullptr) {
		// If first node
		if (init_value_node != nullptr) {
			// The first node is often a ValueNode
			// That is the only time a ValueNode will be the active or root node
			
			// Makes node the new active_node
			node->AddChild(init_value_node);
		}
		active_node = node;
		return;
	}
	FindInsertionNode(node);
	if (IsNary(node->GetOperator()) && node->GetOperator() == active_node->GetOperator()) {
		// TODO: Add node's children to active_node's children

		// Adding node would be a duplicate of active_node for an Nary operator
		return;
	}
	// The new node is a lower priority than any node so far
	// Add new node to top
	if (node->GetPriority() > active_node->GetPriority()) {
		if (active_node->GetPriority() == Priority::OVERRIDE) {
			InsertOperNode(node);
		}
		else if (active_node->IsRoot()) {
			// node is new root
			active_node->InsertAbove(node);
		}
	}
	else if (node->GetOperator() == active_node->GetOperator()) {
		// TODO: Add node's children to active_node
		
		// Adding node would be a duplicate of active_node
		return;
	}
	else {
		InsertOperNode(node);
	}
	active_node = node;
}

/// <summary>
/// Finds insertion point for node and changes active_node to it
/// </summary>
/// <param name="node">Node to insert</param>
void ExpTree::FindInsertionNode(ExpNode *node) {
	// Raises active_node till it's of equal or greater priority to node
	while ((active_node->GetPriority() != Priority::OVERRIDE &&
		node->GetPriority() > active_node->GetPriority()) &&
		!active_node->IsRoot()) {
		active_node = active_node->GetParent();
	}
}

/// <summary>
/// Inserts an OperNode differently depending on it's oper type
/// </summary>
void ExpTree::InsertOperNode(OperNode* node) {
	if (IsUnary(node->GetOperator())) {
		// Adds child if Unary
		active_node->AddChild(node);
	}
	else {
		// Inserts child for Nary
		active_node->InsertChild(node);
	}
}

/// <summary>
/// Add an ValueNode to the tree
/// </summary>
/// <param name="node">ValueNode to add to tree</pararm>
void ExpTree::AddNode(ValueNode *node) {
	if (active_node == nullptr) {
		// If first node
		init_value_node = node;
	}
	else {
		active_node->AddChild(node);
	}
}

/// <summary>
/// Finds the closest UNRESOLVED_PARENTHESIS and change it to PARENTHESIS. 
/// Then, set that node as active_node
/// </summary>
void ExpTree::CloseParenthesis() {

	// Finds UNRESOLVED_PARENTHESIS node
	OperNode* node = active_node;
	while (node->GetPriority() != Priority::OVERRIDE && !node->IsRoot())
	{
		node = node->GetParent();
	}

	if (node->GetPriority() != Priority::OVERRIDE) {
		// No UNRESOLVED_PARENTHESIS in tree
		throw;
	}
	
	// Resolves UNRESOLVED_PARENTHESIS node and make active_node
	((UOperNode*)node)->RemoveOverride(); // TODO: Remove cast
	active_node = node;
}

/// <summary>
/// Get the expression tree printed
/// </summary>
/// <returns>The expression tree as a string</returns>
string ExpTree::Print() {
	// Find root node
	ExpNode* root_node = active_node;
	if (root_node == nullptr) {
		root_node = init_value_node;
	}
	while (!root_node->IsRoot())
	{
		root_node = root_node->GetParent();
	}

	return root_node->Print();
}
