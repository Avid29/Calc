#pragma once

#include "BOperNode.h"
#include "FValueNode.h"
#include "IValueNode.h"
#include "NOperNode.h"
#include "UOperNode.h"
#include "ValueNode.h"

unique_ptr<NOperNode> Add(const ExpNode& left, const ExpNode& right);

unique_ptr<NOperNode> Add(const ExpNode& node, double n);

unique_ptr<NOperNode> Multiply(const ExpNode& left, const ExpNode& right);

unique_ptr<NOperNode> Multiply(const ExpNode& node, double n);

unique_ptr<BOperNode> Power(const ExpNode& left, const ExpNode& right);

unique_ptr<BOperNode> Power(const ExpNode& node, double n);

unique_ptr<UOperNode> Negative(const ExpNode& child);

unique_ptr<UOperNode> Negative(unique_ptr<ExpNode> child);

unique_ptr<ValueNode> MakeValueNode(double value);