#include <string>
#include <vector>

#include "../include/ExpNode.h"
#include "../include/OperNode.h"

using namespace std;

// Get Operator
Operator OperNode::GetOperator() {
	return oper_;
}

// Get Priority 
Priority OperNode::GetPriority() {
	switch (oper_) {
		case ADDITION:
				return ADD;
		case MULTIPLICATION:
				return MULT;
		case POWER:
				return POW;
	}
	return VALUE;
}
