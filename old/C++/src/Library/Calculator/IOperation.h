#pragma once

#include <memory>
#include <string>

using namespace std;

class ExpNode;
class BOperNode;
class DiffOperNode;
class FValueNode;
class IntegralOperNode;
class IValueNode;
class NOperNode;
class SinusoidalOperNode;
class TensorNode;
class UOperNode;
class VarValueNode;

class IOperation
{
public:
	virtual unique_ptr<ExpNode> Execute(const BOperNode& node) = 0;

	virtual unique_ptr<ExpNode> Execute(const DiffOperNode& node) = 0;

	virtual unique_ptr<ExpNode> Execute(const FValueNode& node) = 0;

	virtual unique_ptr<ExpNode> Execute(const IntegralOperNode& node) = 0;

	virtual unique_ptr<ExpNode> Execute(const IValueNode& node) = 0;

	virtual unique_ptr<ExpNode> Execute(const NOperNode& node) = 0;

	virtual unique_ptr<ExpNode> Execute(const SinusoidalOperNode& node) = 0;

	virtual unique_ptr<ExpNode> Execute(const TensorNode& node) = 0;

	virtual unique_ptr<ExpNode> Execute(const UOperNode& node) = 0;

	virtual unique_ptr<ExpNode> Execute(const VarValueNode& node) = 0;
};
