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
					cache_ += "+";
				}
				break;
			}
			case Operator::MULTIPLICATION:
				// TODO: better implied multiplication
				if (!finalPrint) {
					cache_ += "*";
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
	switch (node.GetOperator()) {
	case Operator::POSITIVE:
		// Consider wheather or not to print unary plus
		buffer.append("+");
		buffer.append(node.GetChild(0).Print(*this));
		break;
	case Operator::NEGATIVE:
		buffer.append("-");
		if (child != nullptr) {
			buffer.append(child->Print(*this));
		}
		break;
	case Operator::UNRESOLVED_PARENTHESIS:
	case Operator::PARENTHESIS:
		buffer.append("(");
		if (child != nullptr) {
			buffer.append(child->Print(*this));
			buffer.append(")");
		}
		break;
	case Operator::SINE:
		buffer.append("sin(");
		if (child != nullptr) {
			buffer.append(child->Print(*this));
			buffer.append(")");
		}
		break;
	case Operator::COSINE:
		buffer.append("cos(");
		buffer.append(child->Print(*this));
		buffer.append(")");
		break;
	case Operator::TANGENT:
		buffer.append("tan(");
		buffer.append(child->Print(*this));
		buffer.append(")");
		break;
	case Operator::COSECANT:
		buffer.append("csc(");
		buffer.append(child->Print(*this));
		buffer.append(")");
		break;
	case Operator::SECANT:
		buffer.append("sec(");
		buffer.append(child->Print(*this));
		buffer.append(")");
		break;
	case Operator::COTANGENT:
		buffer.append("cot(");
		buffer.append(child->Print(*this));
		buffer.append(")");
		break;
	}
	return buffer;
}

string DisplayPrinter::Print(const VarValueNode& node) const {
	return string(1, node.GetCharacter());
}
