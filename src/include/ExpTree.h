#pragma once

#include <memory>
#include <string>

#include "ExpNode.h"
#include "FValueNode.h"
#include "IValueNode.h"
#include "OperNode.h"
#include "ValueNode.h"

using namespace std;

class ExpTree {
	public:
		ExpTree();
		void AddNode(OperNode *node);
		void AddNode(ValueNode *node);

		string Print(); 

	private:
		ExpNode *active_node;
		// TODO: Better memory management: unique_ptr<ExpNode> root_node;
};
