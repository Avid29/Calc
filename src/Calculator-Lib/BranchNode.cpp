
#include <string>
#include <vector>

#include "BranchNode.h"

using namespace std;

/// <summary>
/// Checks if node can be represented as a double
/// </summary>
/// <returns>true if node can be represented as a double</returns>
bool BranchNode::IsNumericalValue() const {
	return false;
}

/// <summary>
/// Checks if node is a value
/// </summary>
/// <returns>true if node is a value</returns>
bool BranchNode::IsValue() const {
	return false;
}

/// <summary>
/// Gets this as a double, if possible
/// </summary>
/// <returns>this node as a double value or NAN if not possible</returns>
double BranchNode::AsDouble() const {
	return NAN;
}

bool BranchNode::IsOperNode() const {
	return false;
}

const OperNode* BranchNode::AsOperNode() const {
	return nullptr;
}
