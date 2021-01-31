#include "Helper.h"

unique_ptr<NOperNode> Add(const ExpNode& left, const ExpNode& right) {
	unique_ptr<NOperNode> aNode = make_unique<NOperNode>(Operator::ADDITION);
	aNode->AddChild(left.Clone());
	aNode->AddChild(right.Clone());
	return aNode;
}

unique_ptr<NOperNode> Add(const ExpNode& node, int i) {
	return Add(node, *MakeValueNode(i));
}

unique_ptr<NOperNode> Multiply(const ExpNode& left, const ExpNode& right) {
	unique_ptr<NOperNode> mNode = make_unique<NOperNode>(Operator::MULTIPLICATION);
	mNode->AddChild(left.Clone());
	mNode->AddChild(right.Clone());
	return mNode;
}

unique_ptr<BOperNode> Power(const ExpNode& left, const ExpNode& right) {
	unique_ptr<BOperNode> bNode = make_unique<BOperNode>(Operator::POWER);
	bNode->AddChild(left.Clone());
	bNode->AddChild(right.Clone());
	return bNode;
}

unique_ptr<UOperNode> Negative(const ExpNode& child)
{
	unique_ptr<UOperNode> negNode = make_unique<UOperNode>(Operator::NEGATIVE);
	negNode->AddChild(child.Clone());
	return negNode;
}

unique_ptr<UOperNode> Negative(unique_ptr<ExpNode> child)
{
	unique_ptr<UOperNode> negNode = make_unique<UOperNode>(Operator::NEGATIVE);
	negNode->AddChild(move(child));
	return negNode;
}

