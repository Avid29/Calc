#include <memory>

#include "../include/ExpNode.h"
#include "../include/ExpTree.h"
#include "../include/FValueNode.h"
#include "../include/IValueNode.h"
#include "../include/OperNode.h"
#include "../include/ValueNode.h"

using namespace std;

ExpTree::ExpTree() {}

/// <summary>
/// Add an OperNode to the tree
/// </summary>
/// <param name="node">OperNode to add to tree</pararm>
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
