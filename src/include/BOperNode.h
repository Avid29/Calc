#pragma once

#include <memory>
#include <string>
#include <vector>

#include "ExpNode.h"
#include "OperNode.h"

using namespace std;

class BOperNode : OperNode {
	public:
		virtual void AddChild(::ExpNode *node);

		string Print();
	protected:
		::ExpNode *left_child;
		::ExpNode *right_child;
};
