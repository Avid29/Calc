#include <memory>

#include "../include/ExpNode.h"
#include "../include/ExpTree.h"
#include "../include/FValueNode.h"
#include "../include/IValueNode.h"
#include "../include/OperNode.h"
#include "../include/ValueNode.h"

using namespace std;

ExpTree::ExpTree() {}

void ExpTree::AddNode(OperNode *node) {
	if (active_node == nullptr) {
		active_node = node;
	} else {
		active_node = active_node->AddNode(node);
	}
}

void ExpTree::AddNode(ValueNode *node) {
	if (active_node == nullptr) {
		active_node = node;
	} else {
		active_node = active_node->AddNode(node);	
	}
}

string ExpTree::Print() {
	ExpNode* root_node = active_node;
	while (!root_node->IsRoot())
	{
		printf("\nNew Root!");
		root_node = root_node->GetParent();
	}
	return root_node->Print();
}
