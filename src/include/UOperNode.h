#pragma once

#include <string>
#include <vector>

#include "ExpNode.h"
#include "OperNode.h"

using namespace std;

class UOperNode : OperNode {
	public:
		virtual void AddChild(::ExpNode *node);

		string Print();

	protected:
		::ExpNode *child_;
};
