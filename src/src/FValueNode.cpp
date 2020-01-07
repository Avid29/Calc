#include <string>

#include "../include/ExpNode.h"
#include "../include/FValueNode.h"
#include "../include/IValueNode.h"
#include "../include/ValueNode.h"

using namespace std;

double FValueNode::GetValue() {
	return f_value;
}

void FValueNode::SetValue(double value) {
	f_value = value;
}

string FValueNode::Print() {
	return to_string(f_value);
}

Priority FValueNode::GetPriority() {
	return VALUE;
}