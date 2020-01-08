#include <string>

#include "../include/ExpNode.h"
#include "../include/FValueNode.h"
#include "../include/IValueNode.h"
#include "../include/ValueNode.h"

using namespace std;

IValueNode::IValueNode(int value) : i_value (value) {}

// returns the value of the node
int IValueNode::GetValue() {
	return i_value;
}

// Set the value of the node
void IValueNode::SetValue(int value) {
	i_value = value;
}

// return value of node as a string
string IValueNode::Print() {
	return to_string(i_value); 
}

// IValueNode Priority is VALUE
Priority IValueNode::GetPriority() {
	return VALUE;
}