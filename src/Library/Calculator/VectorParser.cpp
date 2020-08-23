#include "VectorParser.h"

VectorParser::VectorParser()
{
	child_parser = make_unique<InternalParser>();
	vector_ = make_unique<TensorNode>(1);
}

PartialStatus VectorParser::ParseFirstChar(const char c ) {
	if (c == '<') {
		return PartialStatus();
;	}
	return PartialStatus(ErrorTypes::ErrorType::UNKNOWN);
}

PartialStatus VectorParser::ParseNextChar(const char c, unique_ptr<BranchNode>& outputNode) {
	if ((c == ',' || c == '>') && depth_ == 0) {
		Status error = child_parser->Finalize();
		if (error.Failed()) {
			return PartialStatus(error);
		}

		unique_ptr<ExpTree> tree = child_parser->GetTree();
		child_parser = make_unique<InternalParser>();
		if (tree == nullptr) {
			return PartialStatus(ErrorTypes::ErrorType::UNKNOWN);
		}

		vector_->AddChild(tree->GetRoot());

		if (c == '>') {
			vector_->EndDimension((int)TensorType::Vector);
			outputNode = move(vector_);
		}

		return PartialStatus();
	}
	else {
		if (c == '<') {
			depth_++;
		}
		else if (c == '>') {
			depth_--;
		}
		Status result = child_parser->ParseNextChar(c);
		return PartialStatus(result);
	}
}
