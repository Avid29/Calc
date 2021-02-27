#include "Helper.h"

unique_ptr<NOperNode> Add(const ExpNode& left, const ExpNode& right) {
	unique_ptr<NOperNode> aNode = make_unique<NOperNode>(Operator::ADDITION);
	aNode->AddChild(left.Clone());
	aNode->AddChild(right.Clone());
	return aNode;
}

unique_ptr<NOperNode> Add(const ExpNode& node, double n) {
	return Add(node, *MakeValueNode(n));
}
unique_ptr<NOperNode> Subtract(const ExpNode& left, const ExpNode& right) {
	unique_ptr<NOperNode> aNode = make_unique<NOperNode>(Operator::ADDITION);
	aNode->AddChild(left.Clone());

	unique_ptr<UOperNode> uNode = make_unique<UOperNode>(Operator::NEGATIVE);
	uNode->AddChild(right.Clone());
	aNode->AddChild(move(uNode));
	return aNode;
}

unique_ptr<NOperNode> Multiply(const ExpNode& left, const ExpNode& right) {
	unique_ptr<NOperNode> mNode = make_unique<NOperNode>(Operator::MULTIPLICATION);
	mNode->AddChild(left.Clone());
	mNode->AddChild(right.Clone());
	return mNode;
}

unique_ptr<NOperNode> Multiply(const ExpNode& node, double n) {
	return Multiply(node, *MakeValueNode(n));
}

unique_ptr<BOperNode> Power(const ExpNode& left, const ExpNode& right) {
	unique_ptr<BOperNode> bNode = make_unique<BOperNode>(Operator::POWER);
	bNode->AddChild(left.Clone());
	bNode->AddChild(right.Clone());
	return bNode;
}

unique_ptr<BOperNode> Power(const ExpNode& node, double n) {
	return Power(node, *MakeValueNode(n));
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

unique_ptr<UOperNode> Reciprical(const ExpNode& child) {
	unique_ptr<UOperNode> negNode = make_unique<UOperNode>(Operator::RECIPROCAL);
	negNode->AddChild(child.Clone());
	return negNode;
}

unique_ptr<UOperNode> Reciprical(unique_ptr<ExpNode> child) {
	unique_ptr<UOperNode> negNode = make_unique<UOperNode>(Operator::RECIPROCAL);
	negNode->AddChild(move(child));
	return negNode;
}

unique_ptr<ValueNode> MakeValueNode(double value) {
	if (floor(value) == value) {
		return make_unique<IValueNode>((int)value);
	}
	else {
		return make_unique<FValueNode>(value);
	}
}
