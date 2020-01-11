#include "include/AdditiveTerm.h"
#include "include/NOperNode.h"
#include "include/ValueNode.h"

/// <summary>
/// Finds AdditiveTerm to represent node
/// </summary>
AdditiveTerm::AdditiveTerm(ExpNode *node) {
	if (!node->IsValue() && ((OperNode*)node)->GetOperator() == Operator::MULTIPLICATION
		&& ((OperNode*)node)->GetChild(0)->IsNumericalValue()) {
		// Node is a multiply and it's first child is a numerical value
		OperNode *operNode = (OperNode*)node;
		coefficient_ = operNode->GetChild(0)->AsDouble();
		
		if (operNode->ChildCount() > 2) {
			NOperNode *nOperNode = new NOperNode('*');
			for (int i = 1; i < operNode->ChildCount(); i++) {
				nOperNode->AddChild(operNode->GetChild(i));
			}
			base_ = nOperNode;
		}
		else {
			base_ = operNode->GetChild(1);
		}
		base_string = base_->Print();
	}
	else {
		coefficient_ = 1;
		base_ = node;
		base_string = base_->Print();
	}
}

/// <summary>
/// Gets Term as an ExpNode
/// </summary>
ExpNode *AdditiveTerm::AsExpNode() {
	if (coefficient_ == 1) {
		return base_;
	}
	else {
		NOperNode *operNode = new NOperNode('*');
		operNode->AddChild(GetValueNode(coefficient_));
		operNode->AddChild(base_);
		return operNode;
	}
}

/// <summary>
/// Adds coefficients
/// </summary>
void AdditiveTerm::AddToCoefficient(AdditiveTerm *other) {
	coefficient_ += other->coefficient_;
}

/// <summary>
/// Checks if two AdditiveTerm have the same base
/// </summary>
bool AdditiveTerm::CompareBase(const AdditiveTerm &other) {
	return base_string == other.base_string;
}
