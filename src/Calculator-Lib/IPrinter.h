#pragma once

#include <string>

#include "BOperNode.h"
#include "DiffOperNode.h"
#include "FValueNode.h"
#include "IValueNode.h"
#include "NOperNode.h"
#include "UOperNode.h"
#include "VarValueNode.h"

class IPrinter
{
public:
	virtual string Print(const BOperNode& node) = 0;

	virtual string Print(const DiffOperNode& node) = 0;

	virtual string Print(const FValueNode& node) = 0;

	virtual string Print(const IValueNode& node) = 0;

	virtual string Print(const NOperNode& node) = 0;

	virtual string Print(const UOperNode& node) = 0;

	virtual string Print(const VarValueNode& node) = 0;
};
