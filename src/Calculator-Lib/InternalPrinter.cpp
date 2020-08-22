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

string InternalPrinter::PrintError(const Error& error) const {
	ostringstream sstream;
	sstream << endl;
	sstream << error.GetInput() << endl << PrintErrorPosition(DetermineErrorDisplayPositions(error), error.GetInput().size());
	sstream << endl;
	sstream << PrintErrorMessage(error);
	sstream << endl;
	return sstream.str();
}

string InternalPrinter::PrintErrorMessage(const Error& error) const {
	string input = error.GetInput();
	int position = error.GetPosition();
	char invalidChar = input[position];
	ostringstream sstream;
	sstream << "Error: ";

	switch (error.GetErrorType())
	{
	case Error::ErrorType::ALREADY_FLOAT:
		sstream << "'";
		sstream << invalidChar;
		sstream << "' is not an acceptable character because the number is already a float";
		return sstream.str();
	case Error::ErrorType::CANNOT_BEGIN:
		sstream << "Expression cannot begin with '";
		sstream << invalidChar;
		sstream << "'";
		return sstream.str();
	case Error::ErrorType::CANNOT_PROCEED:
		sstream << "'";
		sstream << invalidChar;
		sstream << "' cannot proceed '";
		sstream << input[position - 1];
		sstream << "'";
		return sstream.str();
	case Error::ErrorType::UNPAIRED_PARENTHESIS:
		sstream << "A parenthesis is unpaired.";
		return sstream.str();
	case Error::ErrorType::INVALID_FUNCTION: {
		string functionName;
		for (int i = position - 1; isalpha(input[i]); i--)
		{
			functionName = input[i] + functionName;
		}
		sstream << "No function with the name \"";
		sstream << functionName;
		sstream << "\" was found.";
		return sstream.str();
	}
	case Error::ErrorType::DERIVATIVE_MUST_BE_VARIABLE:
		sstream << "The [] in a \\diff function must contain a single variable";
		return sstream.str();
	case Error::ErrorType::NONE:
		sstream << "An unspecified error occured in parsing '";
		sstream << invalidChar;
		sstream << "'";
		return sstream.str();
	case Error::ErrorType::UNKNOWN:
		sstream << "Unknown error occured in parsing '";
		sstream << invalidChar;
		sstream << "'";
		return sstream.str();
	default:
		sstream << "A known error occured parsing '";
		sstream << invalidChar;
		sstream << "', but the printer doesn't know what it means";
		return sstream.str();
	}
}

string InternalPrinter::PrintErrorPosition(unique_ptr<bool[]> positions, int length) const {
	ostringstream sstream;
	for (int i = 0; i < length; i++)
	{
		if (positions[i]) {
			sstream << "^";
		}
		else {
			sstream << '~';
		}
	}
	return sstream.str();
}

unique_ptr<bool[]> InternalPrinter::DetermineErrorDisplayPositions(const Error& error) const {
	switch (error.GetErrorType())
	{
	case Error::ErrorType::INVALID_FUNCTION: {
		string input = error.GetInput();
		unique_ptr<bool[]> positions(new bool[input.size()]);
		std::fill(positions.get(), positions.get() + error.GetInput().size(), false);
		for (int i = error.GetPosition() - 1; isalpha(input[i]); i--)
		{
			positions[i] = true;
		}
		return positions;
	}
	default: {
		unique_ptr<bool[]> positions(new bool[error.GetInput().size()]);
		std::fill(positions.get(), positions.get() + error.GetInput().size(), false);
		positions[error.GetPosition()] = true;
		return positions;
	}
	}
}
