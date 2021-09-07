#pragma once

#include "EnumerableCollectionNode.h"

enum class TensorType {
	Vector = 1,
	Matrix = 2,
	Tensor
};

class TensorNode : public EnumerableCollectionNode {
	public:
		/// <summary>
		/// Copy constructor
		/// </summary>
		TensorNode(const TensorNode& other);

		TensorNode(int dimensions, TensorType type);

		~TensorNode();

		int GetDimensionCount() const;

		TensorType GetTensorType() const;

		/// <summary>
		/// Gets the size of a dimension
		/// </summary>
		/// <remarks>
		/// Dimensions are 1 indexed
		/// </remarks>
		/// <param name="dimension">The dimension to check</param>
		/// <returns>The size of the dimension</returns>
		int GetDimensionSize(int dimension) const;

		/// <summary>
		/// Finishes adding to a dimension from adding children.
		/// </summary>
		/// <remarks>
		/// Dimensions are 1 indexed
		/// </remarks>
		/// <param name="dimension">The dimension to finish</param>
		/// <returns>The length of the dimension or 0 if invalid.</returns>
		int EndDimension(int dimension);

		unique_ptr<ExpNode> Execute(IOperation* operation) const override;

		string Print(const IPrinter& printer) const override;

		unique_ptr<ExpNode> Clone() const override;

	private:
		TensorType type_;
		int dimensions_;
		int *sizes_;
};

string GetTensorNodeSizeIdentity(const TensorNode& node);