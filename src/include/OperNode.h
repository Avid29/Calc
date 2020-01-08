#pragma once

#include <string>
#include <memory>

#include "ExpNode.h"

using namespace std;

enum Operator {
	ADDITION,
	MULTIPLICATION,
	POWER,
	POS,
	NEG
};

class OperNode : public ExpNode {
	public:
		virtual void AddChild(ExpNode *node) = 0;
		virtual void InsertChild(OperNode *node) = 0;

		virtual string Print() = 0;

		Priority GetPriority();

		Operator GetOperator();

	protected:
		Operator oper_;	
};
