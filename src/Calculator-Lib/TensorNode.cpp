#include "TensorNode.h"

TensorNode::TensorNode(const TensorNode& other) {
	dimensions_ = other.dimensions_;
	for (const unique_ptr<ExpNode>& child : other.children_)
	{
		AddChild(child->Clone());
	}
	sizes_ = new int[(int)dimensions_];
	for (int i = 0; i < (int)dimensions_; i++)
	{
		sizes_[i] = other.sizes_[i];
	}
}

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
	return sizes_[dimension-1];
}

int TensorNode::EndDimension(int dimension) {
	// TODO: Tensors and Matricies
	sizes_[dimension-1] = children_.size();
	return sizes_[dimension-1];
}

unique_ptr<ExpNode> TensorNode::Execute(IOperation* operation) const {
	unique_ptr<TensorNode> newTensor = make_unique<TensorNode>((int)dimensions_);
	newTensor->sizes_ = new int[(int)dimensions_];
	for (size_t i = 0; i < (int)dimensions_; i++)
	{
		newTensor->sizes_[i] = sizes_[i];
	}
	for (size_t i = 0; i < children_.size(); i++)
	{
		newTensor->AddChild(children_[i]->Execute(operation));
	}
	return newTensor;
}

string TensorNode::Print(const IPrinter& printer) const {
	return "<TempVector>";
}

unique_ptr<ExpNode> TensorNode::Clone() const {
	return make_unique<TensorNode>(*this);
}