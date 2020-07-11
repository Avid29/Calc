#pragma once

#include "BranchNode.h"

using namespace std;

class CollectionNode : public BranchNode {
	public:
		/// <summary>
		/// Adds a child and sets its parent
		/// </summary>
		/// <param name="node">New child node</param>
		virtual void AddChild(unique_ptr<ExpNode> node);

		/// <summary>
		/// Inserts child between this and its last child
		/// </summary>
		/// <param name="node">this's new child node</param>
		virtual void InsertChild(unique_ptr<BranchNode> node);

		/// <summary>
		/// Gets child at index
		/// </summary>
		/// <returns>child at index</returns>
		virtual const ExpNode& GetChild(int index);

		/// <summary>
		/// Gets amount of children
		/// </summary>
		/// <returns>children count</returns>
		virtual int ChildCount() const;

		/// <summary>
		/// Gets the priority based on the oper
		/// </summary>
		/// <returns>Proirity value</returns>
		Priority GetPriority() const override;

	private:
		vector<unique_ptr<ExpNode>> children_;
};
