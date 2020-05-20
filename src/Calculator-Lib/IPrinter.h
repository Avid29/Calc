#pragma once

#include <string>

using namespace std;

class BOperNode;
class DiffOperNode;
class FValueNode;
class IValueNode;
class NOperNode;
class UOperNode;
class VarValueNode;

class IPrinter
{
public:
	virtual string Print(const BOperNode& node) const = 0;

	virtual string Print(const DiffOperNode& node) const = 0;

	virtual string Print(const FValueNode& node) const = 0;

	virtual string Print(const IValueNode& node) const = 0;

	virtual string Print(const NOperNode& node) const = 0;

	virtual string Print(const UOperNode& node) const = 0;

	virtual string Print(const VarValueNode& node) const = 0;
};
