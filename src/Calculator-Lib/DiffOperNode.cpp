#include "DiffOperNode.h"

void DiffOperNode::SetVariable(unique_ptr<VarValueNode> variable) {
	variable_ = move(variable);
}