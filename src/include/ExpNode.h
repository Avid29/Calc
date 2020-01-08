#pragma once

#include <string>
#include <memory>
#include <vector>

using namespace std;

enum Priority {
	VALUE,
	UNARY,
	POW,
	MULT,
	ADD
};

class OperNode;
class ValueNode;

class ExpNode {
	public:
		ExpNode();

		ExpNode *AddNode(OperNode *node);
		ExpNode *AddNode(ValueNode *node);

		void SetParent(OperNode* node);

		void InsertAbove(OperNode *node);

		OperNode *GetParent();

		virtual string Print() = 0;

		// Higher values go above
		virtual Priority GetPriority() = 0;

		bool IsRoot();
	protected:
		OperNode *parent_;
};
