#include <string>
#include <vector>

#include "../include/ExpNode.h"
#include "../include/OperNode.h"
#include "../include/UOperNode.h"

using namespace std;

void UOperNode::AddChild(::ExpNode *node) {
	child_ = node;	
}

string UOperNode::Print() {
	string cache_;
	switch (oper_) {
		case POS:
			cache_ = "+";
			break;
		case NEG:
			cache_ = "-";
			break;
	}
	cache_ += child_->Print();
	return cache_;
}
