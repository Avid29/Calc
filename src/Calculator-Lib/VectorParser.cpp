#include "VectorParser.h"

VectorParser::VectorParser()
{
	child_parser = make_unique<InternalParser>();
	vector_ = make_unique<TensorNode>(1);
}

bool VectorParser::ParseFirstChar(const char c ) {
	return c == '<';
}

bool VectorParser::ParseNextChar(const char c, unique_ptr<BranchNode>& outputNode) {
	if ((c == ',' || c == '>') && depth_ == 0) {
		unique_ptr<ExpTree> tree = child_parser->FinalizeAndReturn();
		EnterErrorState(child_parser->GetError().GetErrorType());
		child_parser = make_unique<InternalParser>();
		if (tree == nullptr) {
			return false;
		}

		vector_->AddChild(tree->GetRoot());

		if (c == '>') {
			vector_->EndDimension((int)TensorType::Vector);
			outputNode = move(vector_);
		}

		return true;
	}
	else {
		if (c == '<') {
			depth_++;
		}
		else if (c == '>') {
			depth_--;
		}
		bool result = child_parser->ParseNextChar(c);
		if (!result) {
			EnterErrorState(child_parser->GetError().GetErrorType());
		}
		return result;
	}
}
