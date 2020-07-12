#include <vector>

#include "ExpNode.h"
#include "OperNode.h"
#include "UOperNode.h"
#include "ValueNode.h"

using namespace std;

ExpNode::ExpNode() : parent_ (nullptr) { }

/// <summary>
/// Sets node as the parent of this
/// </summary>
/// <param name="node">New parent node</param>
void ExpNode::SetParent(BranchNode* node) {
	parent_ = node;
}

/// <summary>
/// Gets parent
/// </summary>
/// <returns>parent</returns>
BranchNode*ExpNode::GetParent() const {
	return parent_;
}

/// <summary>
/// Checks if this has parent (if it does not, it's the root node
/// </summary>
/// <returns>true if this is the root node</returns>
bool ExpNode::IsRoot() {
	return parent_ == nullptr;
}