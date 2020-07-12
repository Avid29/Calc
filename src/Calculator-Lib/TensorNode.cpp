#include "TensorNode.h"

TensorNode::TensorNode(int dimensions) : dimensions_((TensorType)dimensions) {
	sizes_ = new int[dimensions];
}

TensorNode::~TensorNode() {
	delete sizes_;
}

TensorType TensorNode::GetDimensionCount() {
	return dimensions_;
}

int TensorNode::GetDimensionSize(int dimension) {
	return sizes_[dimension];
}
