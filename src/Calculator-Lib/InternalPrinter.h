#pragma once

#include "IPrinter.h"
#include "InternalParser.h"

class InternalPrinter : public IPrinter
{
public:
	string Print(const BOperNode& node) const override;

	string Print(const DiffOperNode& node) const override;

	string Print(const FValueNode& node) const override;

	string Print(const IValueNode& node) const override;

	string Print(const NOperNode& node) const override;

	string Print(const TensorNode& node) const override;

	string Print(const UOperNode& node) const override;

	string Print(const VarValueNode& node) const override;
};
