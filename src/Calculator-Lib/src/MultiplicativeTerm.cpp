#include "include/BOperNode.h"
#include "include/MultiplicativeTerm.h"
#include "include/NOperNode.h"
#include "include/ValueNode.h"


/// <summary>
/// Finds MultiplicativeTerm to represent node
/// </summary>
/// <param name="node">root node of term to convert</param>
MultiplicativeTerm::MultiplicativeTerm(ExpNode *node) {
	if (!node->IsValue() && ((OperNode*)node)->GetOperator() == Operator::POWER) {
		OperNode *operNode = ((OperNode *)node);
		base_ = operNode->GetChild(0);
		exponent_ = operNode->GetChild(1);
	} else
	{
		base_ = node;
		exponent_ = GetValueNode(1);
	}
	base_string = base_->Print();
}

/// <summary>
/// Gets Term as an ExpNode
/// </summary>
ExpNode *MultiplicativeTerm::AsExpNode() {
	if (exponent_->AsDouble() == 1) {
		return base_;
	}
	else {
		BOperNode *node = new BOperNode('^');
		node->AddChild(base_);
		node->AddChild(exponent_);
		return node;
	}
}

/// <summary>
/// Adds exponents
/// </summary>
void MultiplicativeTerm::AddToExponent(MultiplicativeTerm *other) {
	if (!exponent_->IsValue() && ((OperNode*)exponent_)->GetOperator() == Operator::ADDITION ) {
		// If exponent_ root is Addition oper
		((OperNode *)exponent_)->AddChild(other->exponent_);
		exponent_ = exponent_->Simplify();
	}
	else {
		// Makes root addition node for exponent and other exponent
		NOperNode *node = new NOperNode('+');
		node->AddChild(exponent_);
		node->AddChild(other->exponent_);
		exponent_ = node->Simplify();
	}
}

/// <summary>
/// Checks if two MultiplicateTerms have the same base
/// </summary>
bool MultiplicativeTerm::CompareBase(const MultiplicativeTerm &other) {
	return base_string == other.base_string;
}