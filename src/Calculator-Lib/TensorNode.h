#pragma once

#include "EnumerableCollectionNode.h"

enum class TensorType {
	Vector = 1,
	Matrix = 2,
	Tensor
};

class TensorNode : public EnumerableCollectionNode {
	public:
		TensorNode(int dimensions);

		~TensorNode();

		TensorType GetDimensionCount();

		int GetDimensionSize(int dimension);

	private:
		TensorType dimensions_;
		int *sizes_;
};
