#pragma once

#include "ExpNode.h"
#include "ValueNode.h"

class FValueNode : ValueNode {
	public:
		double GetValue();
		void SetValue(double value);

		string Print();

	private:
		double f_value;
};
