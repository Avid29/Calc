#include "AdditiveTerm.h"
#include "NOperNode.h"
#include "ValueNode.h"
#include "InternalPrinter.h"

#include "Helper.h"

/// <summary>
/// Finds AdditiveTerm to represent node
/// </summary>
AdditiveTerm::AdditiveTerm(const ExpNode &node) {
	InternalPrinter *printer = new InternalPrinter();
	const OperNode *operNode = dynamic_cast<const OperNode*>(&node);
	if (operNode != nullptr && operNode->GetOperator() == Operator::MULTIPLICATION
		&& operNode->GetChild(0).IsNumericalValue()) {
		// Node is a multiply and it's first child is a numerical value
		coefficient_ = operNode->GetChild(0).AsDouble();

		if (operNode->ChildCount() > 2) {
			// Makes new multiply node for non-coefficient terms
			unique_ptr<NOperNode> nOperNode = make_unique<NOperNode>('*');
			for (int i = 1; i < operNode->ChildCount(); i++) {
				nOperNode->AddChild(operNode->GetChild(i).Clone());
			}
			base_ = move(nOperNode);
		}
		else {
			base_ = operNode->GetChild(1).Clone();
		}
		base_string = base_->Print(*printer);
	}
	else {
		coefficient_ = 1;
		base_ = node.Clone();
		base_string = base_->Print(*printer);
	}
	delete printer;
}
/// <summary>
/// Gets Term as an ExpNode
/// </summary>
unique_ptr<ExpNode> AdditiveTerm::AsExpNode() {
	if (coefficient_ == 1) {
		return move(base_);
	}
	else {
		unique_ptr<NOperNode> operNode = make_unique<NOperNode>('*');
		operNode->AddChild(MakeValueNode(coefficient_));
		operNode->AddChild(move(base_));
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
bool AdditiveTerm::operator==(const AdditiveTerm &other) {
	return base_string == other.base_string;
}

/// <summary>
/// Compares sort order of this with with
/// </summary>
bool AdditiveTerm::operator<(const AdditiveTerm &other) const {
	if (base_->IsNumericalValue()) {
		return false;
	}
	else if (other.base_->IsNumericalValue()) {
		return true;
	}
	return base_string < other.base_string;
}
