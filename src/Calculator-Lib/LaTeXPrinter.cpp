#include "LaTeXPrinter.h"
#include "BOperNode.h"
#include "DiffOperNode.h"
#include "FValueNode.h"
#include "IValueNode.h"
#include "NOperNode.h"
#include "UOperNode.h"
#include "VarValueNode.h"

string LaTeXPrinter::Print(const BOperNode& node) const {
	string cache_ = "";
	cache_ += node.GetChild(0).Print(*this);

	switch (node.GetOperator()) {
	case Operator::POWER:
		cache_ += "^";
		break;

		cache_ += node.GetChild(1).Print(*this);
		return cache_;
	}
}

string LaTeXPrinter::Print(const DiffOperNode& node) const {
	// TODO: Add GetVariable to DiffOperNode
	return "";
}

string LaTeXPrinter::Print(const FValueNode& node) const {
	return to_string(node.GetValue());
}

string LaTeXPrinter::Print(const IValueNode& node) const {
	return to_string(node.GetValue());
}

string LaTeXPrinter::Print(const NOperNode& node) const {
	string cache_;
	for (unsigned int i = 0; i < node.ChildCount(); i++) {
		if (i != 0) {
			switch (node.GetOperator()) {
			case Operator::ADDITION:
				// TODO: Handle unary '-' child
				cache_ += "+";
				break;
			case Operator::MULTIPLICATION:
				// All remaining multiplication will be implied
				break;
			}
		}
		cache_ += node.GetChild(i).Print(*this);
	}
	return cache_;
}

string LaTeXPrinter::Print(const UOperNode& node) const {
	string buffer = "";
	switch (node.GetOperator()) {
	case Operator::POSITIVE:
		// Consider wheather or not to print unary plus
		buffer.append("+");
		buffer.append(node.GetChild(0).Print(*this));
		break;
	case Operator::NEGATIVE:
		buffer.append("-");
		buffer.append(node.GetChild(0).Print(*this));
		break;
	case Operator::UNRESOLVED_PARENTHESIS:
	case Operator::PARENTHESIS:
		buffer.append("(");
		buffer.append(node.GetChild(0).Print(*this));
		buffer.append(")");
		break;
	case Operator::SINE:
		buffer.append("\\sin{");
		buffer.append(node.GetChild(0).Print(*this));
		buffer.append("}");
		break;
	case Operator::COSINE:
		buffer.append("\\cos{");
		buffer.append(node.GetChild(0).Print(*this));
		buffer.append("}");
		break;
	case Operator::TANGENT:
		buffer.append("\\tan{");
		buffer.append(node.GetChild(0).Print(*this));
		buffer.append("}");
		break;
	case Operator::COSECANT:
		buffer.append("\\csc{");
		buffer.append(node.GetChild(0).Print(*this));
		buffer.append("}");
		break;
	case Operator::SECANT:
		buffer.append("\\sec{");
		buffer.append(node.GetChild(0).Print(*this));
		buffer.append("}");
		break;
	case Operator::COTANGENT:
		buffer.append("\\cot{");
		buffer.append(node.GetChild(0).Print(*this));
		buffer.append("}");
		break;
	}
	return buffer;
}

string LaTeXPrinter::Print(const VarValueNode& node) const {
	// TODO: Add get char to VarValueNode
	return "";
}
