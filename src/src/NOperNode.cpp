#include <memory>
#include <vector>

#include "../include/ExpNode.h"
#include "../include/NOperNode.h"
#include "../include/OperNode.h"

using namespace std;

NOperNode::NOperNode(char c) {
	switch (c) {
		case '+':
			oper_ = ADDITION;
			break;
		case '*':
			oper_ = MULTIPLICATION;
			break;
	}
}

void NOperNode::AddChild(::ExpNode *node) {
	children_.push_back(node);
}

void NOperNode::InsertChild(::OperNode *node) {	
	ExpNode *grand_child = children_.back();
	children_.pop_back();
	grand_child->InsertParent(node);
	AddChild(node);
}


string NOperNode::Print() {
	string cache_;
	for (int i = 0; i < children_.size(); i++) {
		if (i != 0) {
			switch (oper_) {
				case ADDITION:
					cache_ += "+";
					break;
				case MULTIPLICATION:
					cache_ += "*";
					break;
			}
		}
		ExpNode *node = children_[i];
		cache_ += node->Print();	
	}
	return cache_;
}
