#pragma once

#include <memory>
#include <string>
#include <vector>

#include "ExpNode.h"
#include "OperNode.h"

using namespace std;

class NOperNode	: public OperNode {
	public:
		NOperNode();
		NOperNode(char c);

		void AddChild(::ExpNode *node);
		void InsertChild(::OperNode *node);

		string Print();
	protected:
		vector<::ExpNode*> children_;
};
