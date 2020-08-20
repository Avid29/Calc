#include <sstream>

#include "InternalPrinter.h"
#include "BOperNode.h"
#include "DiffOperNode.h"
#include "FValueNode.h"
#include "IValueNode.h"
#include "NOperNode.h"
#include "TensorNode.h"
#include "UOperNode.h"
#include "VarValueNode.h"

string InternalPrinter::Print(const BOperNode& node) const {
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

string InternalPrinter::Print(const DiffOperNode& node) const {
	string buffer = "";
	buffer.append("\\diff[");
	buffer.append(node.GetVariable().Print(*this));
	buffer.append("]{");
	buffer.append(node.GetChild(0).Print(*this));
	buffer.append("}");
	return buffer;
}

string InternalPrinter::Print(const FValueNode& node) const {
	ostringstream oss;
	oss << node.GetValue();
	return oss.str();
}

string InternalPrinter::Print(const IValueNode& node) const {
	return to_string(node.GetValue());
}

string InternalPrinter::Print(const NOperNode& node) const {
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
				// All remaining multiplication will be implied
				break;
			}
		}
		cache_ += node.GetChild(i).Print(*this);
	}
	return cache_;
}

string InternalPrinter::Print(const TensorNode& node) const {
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

string InternalPrinter::Print(const UOperNode& node) const {
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

string InternalPrinter::Print(const VarValueNode& node) const {
	return string(1, node.GetCharacter());
}

string InternalPrinter::PrintError(const InternalParser& parser) const {
	string input = parser.GetInput();
	int position = parser.GetPosition();
	int displayPosition = position + 1; // Display is 1 indexed
	char invalidChar = input[position];
	ostringstream sstream;
	sstream << "Error: ";

	switch (parser.GetError())
	{
	case InternalParser::State::ALREADY_FLOAT:
		sstream << "'";
		sstream << invalidChar;
		sstream << "' is not an acceptable character at position ";
		sstream << displayPosition;
		sstream << " because the number is already a float";
		return sstream.str();
	case InternalParser::State::CANNOT_BEGIN:
		sstream << "Expression cannot begin with '";
		sstream << invalidChar;
		sstream << "'";
		return sstream.str();
	case InternalParser::State::CANNOT_PROCEED:
		sstream << "'";
		sstream << invalidChar;
		sstream << "' cannot proceed '";
		sstream << input[position - 1];
		sstream << "'";
		return sstream.str();
	case InternalParser::State::UNPAIRED_PARENTHESIS:
		sstream << "A parenthesis is unpaired.";
		return sstream.str();
	default:
	case InternalParser::State::UNKNOWN_ERROR:
		sstream << "Unknown error occured in parsing '";
		sstream << invalidChar;
		sstream << "' at ";
		sstream << displayPosition;
		return sstream.str();
	}
}
