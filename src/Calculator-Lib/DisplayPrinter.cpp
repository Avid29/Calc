#include <sstream>

#include "DisplayPrinter.h"
#include "BOperNode.h"
#include "DiffOperNode.h"
#include "FValueNode.h"
#include "IValueNode.h"
#include "NOperNode.h"
#include "TensorNode.h"
#include "UOperNode.h"
#include "VarValueNode.h"

DisplayPrinter::DisplayPrinter(bool final) {
	finalPrint = final;
}

string DisplayPrinter::Print(const BOperNode& node) const {
	string cache_ = "";
	cache_ += node.GetChild(0).Print(*this);

	switch (node.GetOperator()) {
	case Operator::POWER:
		cache_ += "^";
		break;
	}

	cache_ += node.GetChild(1).Print(*this);
	return cache_;
}

string DisplayPrinter::Print(const DiffOperNode& node) const {
	string buffer = "";
	// TODO: Better derivative printing
	buffer.append("((d/d");
	buffer.append(node.GetVariable().Print(*this));
	buffer.append(")");
	buffer.append(node.GetChild(0).Print(*this));
	buffer.append(")");
	return buffer;
}

string DisplayPrinter::Print(const FValueNode& node) const {
	ostringstream oss;
	oss << node.GetValue();
	return oss.str();
}

string DisplayPrinter::Print(const IValueNode& node) const {
	return to_string(node.GetValue());
}

string DisplayPrinter::Print(const NOperNode& node) const {
	string cache_;
	for (unsigned int i = 0; i < node.ChildCount(); i++) {
		if (i != 0) {
			switch (node.GetOperator()) {
			case Operator::ADDITION: {
				const UOperNode* uOperNode = dynamic_cast<const UOperNode*>(node.GetChild(i).Clone().get());
				if (isnan(node.GetChild(i).AsDouble()) ?
					!(uOperNode != nullptr &&
						uOperNode->GetOperator() != Operator::NEGATIVE) :
					node.GetChild(i).AsDouble() > 0) {
					// If child is not unary minus or a negative value
					cache_ += PrintOperatorPrefix(node.GetOperator()); // Adds the "+"
				}
				break;
			}
			case Operator::MULTIPLICATION:
				// TODO: better implied multiplication
				if (!finalPrint) {
					const UOperNode* uOperNode = dynamic_cast<const UOperNode*>(node.GetChild(i).Clone().get());
					if (!(uOperNode != nullptr && uOperNode->GetOperator() != Operator::RECIPROCAL)) {
						cache_ += PrintOperatorPrefix(node.GetOperator()); // Adds the "*"
					}
				}
			}
		}
		cache_ += node.GetChild(i).Print(*this);
	}
	return cache_;
}

string DisplayPrinter::Print(const TensorNode& node) const {
	string progress;
	switch (node.GetDimensionCount())
	{
	case TensorType::Vector:
		progress += "<";
		for (int i = 0; i < node.ChildCount(); i++) {
			progress += node.GetChild(i).Print(*this);
			if (i < node.ChildCount() - 1) {
				progress += ",";
			}
		}
		progress += '>';
		return progress;
	default:
		// TODO: Print matricies and tensors
		return "";
	}
}

string DisplayPrinter::Print(const UOperNode& node) const {

	string buffer = "";
	const ExpNode* child = &node.GetChild(0);
	if (child == nullptr) {
		return buffer;
	}

	switch (node.GetOperator()) {
	case Operator::POSITIVE:
	case Operator::NEGATIVE:
		// Consider wheather or not to print unary plus
		buffer.append(PrintOperatorPrefix(node.GetOperator()));
		buffer.append(node.Print(*this));
		break;
	case Operator::UNRESOLVED_PARENTHESIS:
	case Operator::PARENTHESIS:
	case Operator::SINE:
	case Operator::COSINE:
	case Operator::TANGENT:
	case Operator::COSECANT:
	case Operator::SECANT:
	case Operator::COTANGENT:
		buffer.append(PrintOperatorPrefix(node.GetOperator()));
		buffer.append(child->Print(*this));
		buffer.append(")");
		break;
	}
	return buffer;
}

string DisplayPrinter::Print(const VarValueNode& node) const {
	return string(1, node.GetCharacter());
}

string DisplayPrinter::PrintOperatorPrefix(Operator oper) const {
	switch (oper)
	{
	case Operator::ADDITION:
		return "+";
	case Operator::MULTIPLICATION:
		return "*";
	case Operator::POWER:
		return "^";
	case Operator::POSITIVE:
		return "+";
	case Operator::NEGATIVE:
		return "-";
	case Operator::RECIPROCAL:
		return "/";
	case Operator::SINE:
		return "sin(";
	case Operator::COSINE:
		return "cos(";
	case Operator::TANGENT:
		return "tan(";
	case Operator::COSECANT:
		return "csc(";
	case Operator::SECANT:
		return "sec(";
	case Operator::COTANGENT:
		return "cot(";
	case Operator::DERIVATIVE:
		return "\\diff[";
	case Operator::UNRESOLVED_PARENTHESIS:
		return "(";
	case Operator::PARENTHESIS:
		return "(";
	case Operator::VECTOR:
		return "<";
	default:
		return "?";
	}
}