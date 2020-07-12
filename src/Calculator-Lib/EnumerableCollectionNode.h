#pragma once

#include "BranchNode.h"

using namespace std;

class EnumerableCollectionNode : public BranchNode {
	public:
		/// <summary>
		/// Adds a child and sets its parent
		/// </summary>
		/// <param name="node">New child node</param>
		void AddChild(unique_ptr<ExpNode> node) override;

		/// <summary>
		/// Inserts child between this and its last child
		/// </summary>
		/// <param name="node">this's new child node</param>
		void InsertChild(unique_ptr<BranchNode> node) override;

		/// <summary>
		/// Gets child at index
		/// </summary>
		/// <returns>child at index</returns>
		const ExpNode& GetChild(int index) const override;

		void ClearChildren() override;

		/// <summary>
		/// Gets amount of children
		/// </summary>
		/// <returns>children count</returns>
		int ChildCount() const;

		/// <summary>
		/// Gets the priority of the node
		/// </summary>
		/// <returns>Proirity value</returns>
		Priority GetPriority() const override;

		bool IsConstant() const override;

		bool IsConstantBy(const VarValueNode& node) const override;

	protected:
		vector<unique_ptr<ExpNode>> children_;
};
