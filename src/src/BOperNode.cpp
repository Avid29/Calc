#include <memory>

#include "../include/BOperNode.h"
#include "../include/ExpNode.h"
#include "../include/OperNode.h"

using namespace std;

void BOperNode::AddChild(::ExpNode *node) {
	if (left_child == nullptr) {
		left_child = node;
	} else if (right_child == nullptr) {
		right_child = node;
	} else { 
		throw;
	}
}

string BOperNode::Print() {
	string cache_ = "";
	cache_ += left_child->Print();

	switch (oper_) {
		case POWER:
			cache_ += "^";
			break;
	}

	cache_ += right_child->Print();
	return cache_;
}
