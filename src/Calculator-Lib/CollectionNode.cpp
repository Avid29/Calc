#include "CollectionNode.h"

/// <summary>
/// Adds a child and sets its parent
/// </summary>
/// <param name="node">New child node</param>
void AddChild(unique_ptr<ExpNode> node) {

}

/// <summary>
/// Inserts child between this and its last child
/// </summary>
/// <param name="node">this's new child node</param>
void InsertChild(unique_ptr<BranchNode> node) {

}

/// <summary>
/// Gets child at index
/// </summary>
/// <returns>child at index</returns>
const ExpNode& CollectionNode::GetChild(int index) {
	return *children_[index];
}

/// <summary>
/// Gets amount of children
/// </summary>
/// <returns>children count</returns>
int CollectionNode::ChildCount() const {
	return children_.size();
}

/// <summary>
/// Gets the priority based on the oper
/// </summary>
/// <returns>Proirity value</returns>
Priority CollectionNode::GetPriority() const {
	return Priority::OVERRIDE;
}
