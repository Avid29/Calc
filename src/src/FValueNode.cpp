#include <string>

#include "../include/ExpNode.h"
#include "../include/FValueNode.h"
#include "../include/IValueNode.h"
#include "../include/ValueNode.h"

using namespace std;

// returns the value of the node
double FValueNode::GetValue() {
	return f_value;
}

// Set the value of the node
void FValueNode::SetValue(double value) {
	f_value = value;
}

// return value of node as a string
string FValueNode::Print() {
	return to_string(f_value);
}

// FValueNode Priority is VALUE
Priority FValueNode::GetPriority() {
	return VALUE;
}