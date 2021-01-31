#pragma once

#include "BOperNode.h"
#include "NOperNode.h"
#include "UOperNode.h"
#include "ValueNode.h"

unique_ptr<NOperNode> Add(const ExpNode& left, const ExpNode& right);

unique_ptr<NOperNode> Add(const ExpNode& node, int i);

unique_ptr<NOperNode> Multiply(const ExpNode& left, const ExpNode& right);

unique_ptr<BOperNode> Power(const ExpNode& left, const ExpNode& right);

unique_ptr<UOperNode> Negative(const ExpNode& child);