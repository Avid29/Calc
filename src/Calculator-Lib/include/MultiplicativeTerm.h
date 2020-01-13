#pragma once

#include "OperNode.h"

using namespace std;

class MultiplicativeTerm {
	public:
		/// <summary>
		/// Finds MultiplicativeTerm to represent node
		/// </summary>
		/// <param name="node">root node of term to convert</param>
		MultiplicativeTerm(const ExpNode &node);

		/// <summary>
		/// Gets Term as an ExpNode
		/// </summary>
		unique_ptr<ExpNode> AsExpNode();

		/// <summary>
		/// Adds exponents
		/// </summary>
		void AddToExponent(MultiplicativeTerm *other);

		/// <summary>
		/// Checks if two MultiplicateTerms have the same base
		/// </summary>
		bool CompareBase(const MultiplicativeTerm &other);

		bool operator<(const MultiplicativeTerm &other) const {
			if (base_->IsNumericalValue()) {
				return true;
			}
			else if (other.base_->IsNumericalValue()) {
				return false;
			}
			return base_string < other.base_string;
		}

	private:
		// Used to compare bases
		string base_string;

		unique_ptr<ExpNode> base_;
		unique_ptr<ExpNode> exponent_;
};