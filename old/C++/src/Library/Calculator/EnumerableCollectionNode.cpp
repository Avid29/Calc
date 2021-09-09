#include "EnumerableCollectionNode.h"

/// <summary>
/// Adds a child and sets its parent
/// </summary>
/// <param name="node">New child node</param>
void EnumerableCollectionNode::AddChild(unique_ptr<ExpNode> node) {
	children_.push_back(move(node));
}

/// <summary>
/// Inserts child between this and its last child
/// </summary>
/// <param name="node">this's new child node</param>
void EnumerableCollectionNode::InsertChild(unique_ptr<BranchNode> node) {
	// Gets this's last child and remove from children_
	node->AddChild(move(children_.back()));
	children_.pop_back();
	AddChild(move(node));
}

/// <summary>
/// Gets child at index
/// </summary>
/// <returns>child at index</returns>
const ExpNode& EnumerableCollectionNode::GetChild(int index) const {
	return *children_[index];
}

void EnumerableCollectionNode::ClearChildren() {
	children_.clear();
}

/// <summary>
/// Gets amount of children
/// </summary>
/// <returns>children count</returns>
int EnumerableCollectionNode::ChildCount() const {
	return children_.size();
}

/// <summary>
/// Gets the priority based on the oper
/// </summary>
/// <returns>Proirity value</returns>
Priority EnumerableCollectionNode::GetPriority() const {
	return Priority::VALUE;
}

bool EnumerableCollectionNode::IsConstant() const {
	for (size_t i = 0; i < children_.size(); i++)
	{
		if (!children_[i]->IsConstant()) {
			return false;
		}
	}
	return true;
}

bool EnumerableCollectionNode::IsConstantBy(const VarValueNode& node) const {
	for (size_t i = 0; i < children_.size(); i++)
	{
		if (!children_[i]->IsConstantBy(node)) {
			return false;
		}
	}
	return true;
}