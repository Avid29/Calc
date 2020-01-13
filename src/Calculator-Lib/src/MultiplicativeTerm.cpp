#include "include/BOperNode.h"
#include "include/MultiplicativeTerm.h"
#include "include/NOperNode.h"
#include "include/ValueNode.h"


/// <summary>
/// Finds MultiplicativeTerm to represent node
/// </summary>
/// <param name="node">root node of term to convert</param>
MultiplicativeTerm::MultiplicativeTerm(const ExpNode &node) {
	const OperNode *operNode = dynamic_cast<const OperNode*>(&node);
	if (operNode != nullptr && operNode->GetOperator() == Operator::POWER) {
		base_ = operNode->GetChild(0).Clone();
		exponent_ = operNode->GetChild(1).Clone();
	} else
	{
		base_ = node.Clone();
		exponent_ = MakeValueNode(1);
	}
	base_string = base_->Print();
}

/// <summary>
/// Gets Term as an ExpNode
/// </summary>
unique_ptr<ExpNode> MultiplicativeTerm::AsExpNode() {
	if (exponent_->AsDouble() == 1) {
		return move(base_);
	}
	else {
		unique_ptr<BOperNode> node = make_unique<BOperNode>('^');
		node->AddChild(move(base_));
		node->AddChild(move(exponent_));
		return node;
	}
}

/// <summary>
/// Adds exponents
/// </summary>
void MultiplicativeTerm::AddToExponent(MultiplicativeTerm *other) {
	OperNode *exponentNode = dynamic_cast<OperNode*>(exponent_.get());
	if (exponentNode != nullptr && exponentNode->GetOperator() == Operator::ADDITION ) {
		// If exponent_ root is Addition oper
		exponentNode->AddChild(move(other->exponent_));
		exponent_ = exponent_->Simplify();
	}
	else {
		// Makes root addition node for exponent and other exponent
		unique_ptr<NOperNode> node = make_unique<NOperNode>('+');
		node->AddChild(move(exponent_));
		node->AddChild(move(other->exponent_));
		exponent_ = move(node->Simplify());
	}
}

/// <summary>
/// Checks if two MultiplicateTerms have the same base
/// </summary>
bool MultiplicativeTerm::CompareBase(const MultiplicativeTerm &other) {
	return base_string == other.base_string;
}