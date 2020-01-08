#include <memory>

#include "../include/ExpNode.h"
#include "../include/ExpTree.h"
#include "../include/FValueNode.h"
#include "../include/IValueNode.h"
#include "../include/OperNode.h"
#include "../include/UOperNode.h"
#include "../include/ValueNode.h"

using namespace std;

ExpTree::ExpTree() {}

/// <summary>
/// Add an OperNode to the tree
/// </summary>
/// <param name="node">OperNode to add to tree</param>
void ExpTree::AddNode(OperNode *node) {
	if (active_node == nullptr) {
		// If first node
		active_node = node;
	} else {
		active_node = active_node->AddNode(node);
	}
}

/// <summary>
/// Add an ValueNode to the tree
/// </summary>
/// <param name="node">ValueNode to add to tree</pararm>
void ExpTree::AddNode(ValueNode *node) {
	if (active_node == nullptr) {
		// If first node
		active_node = node;
	} else {
		active_node = active_node->AddNode(node);	
	}
}

/// <summary>
/// Find the closest OVERRIDE and change it to OVERRIDEN. 
/// Then, set OVERRIDE as active_node
/// </summary>
void ExpTree::FinishOverride() {

	// Find OVERRIDE node
	ExpNode* node = active_node;
	while (node->GetPriority() != Priority::OVERRIDE && !node->IsRoot())
	{
		node = node->GetParent();
	}

	if (node->GetPriority() != Priority::OVERRIDE) {
		// No OVERRIDE in tree
		throw;
	}
	
	// Close OVERRIDE node and make active
	((UOperNode*)node)->RemoveOverride();
	active_node = node;
}

/// <summary>
/// Get the expression tree printed
/// </summary>
/// <returns>The expression tree as a string</returns>
string ExpTree::Print() {
	// Find root node
	ExpNode* root_node = active_node;
	while (!root_node->IsRoot())
	{
		root_node = root_node->GetParent();
	}

	return root_node->Print();
}
