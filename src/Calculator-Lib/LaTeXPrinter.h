#pragma once

#include "IPrinter.h"

class LaTeXPrinter : public IPrinter
{
public:
	string Print(const BOperNode& node) const;

	string Print(const DiffOperNode& node) const;

	string Print(const FValueNode& node) const;

	string Print(const IValueNode& node) const;

	string Print(const NOperNode& node) const;

	string Print(const UOperNode& node) const;

	string Print(const VarValueNode& node) const;
};
