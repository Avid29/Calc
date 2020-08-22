#include "VectorParser.h"

VectorParser::VectorParser()
{
	child_parser = make_unique<InternalParser>();
	vector_ = make_unique<TensorNode>(1);
}

PartialError VectorParser::ParseFirstChar(const char c ) {
	if (c == '<') {
		return PartialError();
;	}
	return PartialError(ErrorTypes::ErrorType::UNKNOWN);
}

PartialError VectorParser::ParseNextChar(const char c, unique_ptr<BranchNode>& outputNode) {
	if ((c == ',' || c == '>') && depth_ == 0) {
		Error error = child_parser->Finalize();
		if (error.Occured()) {
			return PartialError(error);
		}

		unique_ptr<ExpTree> tree = child_parser->GetTree();
		child_parser = make_unique<InternalParser>();
		if (tree == nullptr) {
			return PartialError(ErrorTypes::ErrorType::UNKNOWN);
		}

		vector_->AddChild(tree->GetRoot());

		if (c == '>') {
			vector_->EndDimension((int)TensorType::Vector);
			outputNode = move(vector_);
		}

		return PartialError();
	}
	else {
		if (c == '<') {
			depth_++;
		}
		else if (c == '>') {
			depth_--;
		}
		Error result = child_parser->ParseNextChar(c);
		return PartialError(result);
	}
}
