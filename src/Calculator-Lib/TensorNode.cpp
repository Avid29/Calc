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

TensorType TensorNode::GetDimensionCount() const {
	return dimensions_;
}

int TensorNode::GetDimensionSize(int dimension) const {
	return sizes_[dimension-1];
}

int TensorNode::EndDimension(int dimension) {
	// TODO: Tensors and Matricies
	sizes_[dimension-1] = children_.size();
	return sizes_[dimension-1];
}

unique_ptr<ExpNode> TensorNode::Execute(IOperation* operation) const {
	return operation->Execute(*this);
}

string TensorNode::Print(const IPrinter& printer) const {
	return printer.Print(*this);
}

unique_ptr<ExpNode> TensorNode::Clone() const {
	return make_unique<TensorNode>(*this);
}

string GetTensorNodeSizeIdentity(const TensorNode& node) {
	string str = "";
	for (int i = 1; i <= (int)node.GetDimensionCount(); i++)
	{
		str += node.GetDimensionSize(i);
		str += ',';
	}
	return str;
}