#include "BOperNode.h"
#include "MultiplicativeTerm.h"
#include "NOperNode.h"
#include "ValueNode.h"
#include "LaTeXPrinter.h"


/// <summary>
/// Finds MultiplicativeTerm to represent node
/// </summary>
/// <param name="node">root node of term to convert</param>
MultiplicativeTerm::MultiplicativeTerm(const ExpNode &node) {
	LaTeXPrinter* printer = new LaTeXPrinter();
	const OperNode *operNode = dynamic_cast<const OperNode*>(&node);
	if (operNode != nullptr && operNode->GetOperator() == Operator::POWER) {
		base_ = operNode->GetChild(0).Clone();
		exponent_ = operNode->GetChild(1).Clone();
	} else
	{
		base_ = node.Clone();
		exponent_ = MakeValueNode(1);
	}
	base_string = base_->Print(*printer);
	delete printer;
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
void MultiplicativeTerm::AddToExponent(MultiplicativeTerm *other, IOperation* operation) {
	OperNode *exponentNode = dynamic_cast<OperNode*>(exponent_.get());
	if (exponentNode != nullptr && exponentNode->GetOperator() == Operator::ADDITION ) {
		// If exponent_ root is Addition oper
		exponentNode->AddChild(move(other->exponent_));
		exponent_ = exponent_->Execute(operation);
	}
	else {
		// Makes root addition node for exponent and other exponent
		unique_ptr<NOperNode> node = make_unique<NOperNode>('+');
		node->AddChild(move(exponent_));
		node->AddChild(move(other->exponent_));
		exponent_ = move(node->Execute(operation));
	}
}

/// <summary>
/// Compares sort order of this with with
/// </summary>
bool MultiplicativeTerm::operator<(const MultiplicativeTerm &other) const {
	if (base_->IsNumericalValue()) {
		// Numbers first
		return true;
	}
	else if (other.base_->IsNumericalValue()) {
		// Numbers first
		return false;
	}
	else if (base_string[0] == '(') {
		// Parenthesis last
		return false;
	}
	else if (other.base_string[0] == '(') {
		// Parenthesis last
		return true;
	}
	// Arbitrary comparsing to confirm order of like terms
	return base_string < other.base_string;
}

/// <summary>
/// Checks if two MultiplicateTerms have the same base
/// </summary>
bool MultiplicativeTerm::operator==(const MultiplicativeTerm &other) const {
	return base_string == other.base_string && base_string[0] != '(';
}