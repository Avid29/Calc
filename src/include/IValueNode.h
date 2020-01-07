#pragma once

#include "ExpNode.h"
#include "ValueNode.h"

class IValueNode : public ValueNode {
	public:
		IValueNode();
		IValueNode(int value);

		int GetValue();
		void SetValue(int value);

		string Print();
	private:
		int i_value;
};
