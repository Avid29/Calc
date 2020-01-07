#include <string>

#include "../include/ExpNode.h"
#include "../include/FValueNode.h"
#include "../include/IValueNode.h"
#include "../include/ValueNode.h"

using namespace std;

IValueNode::IValueNode(int value) : i_value (value) {}

int IValueNode::GetValue() {
	return i_value;
}

void IValueNode::SetValue(int value) {
	i_value = value;
}

string IValueNode::Print() {
	return to_string(i_value); 
}

Priority IValueNode::GetPriority() {
	return VALUE;
}