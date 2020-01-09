#include <vector>

#include "../include/ExpNode.h"
#include "../include/OperNode.h"
#include "../include/UOperNode.h"
#include "../include/ValueNode.h"

using namespace std;

ExpNode::ExpNode() : parent_ (nullptr) { }

/// <summary>
/// Set node as the parent of this
/// </summary>
/// <param name="node">New parent node</param>
void ExpNode::SetParent(OperNode* node) {
	parent_ = node;
}

/// <summary>
/// Set node as the parent of this and this as the child of node
/// </summary>
/// <param name="node">New parent node</param>
void ExpNode::InsertAbove(OperNode *node) {
	node->AddChild(this);
	SetParent(node);
}

/// <summary>
/// Get parent_
/// </summary>
/// <returns>parent_</returns>
OperNode *ExpNode::GetParent() {
	return parent_;
}
/// <summary>
/// Checks if this has parent (if it does not, it's the root node
/// </summary>
/// <returns>true if this is the root node</returns>
bool ExpNode::IsRoot() {
	return parent_ == nullptr;
}
