#pragma once

#include "include/ExpNode.h"

using namespace std;

class AdditiveTerm {
	public:
		/// <summary>
		/// Finds AdditiveTerm to represent node
		/// </summary>
		AdditiveTerm(const ExpNode &node);

		/// <summary>
		/// Gets Term as an ExpNode and clears state.
		/// </summary>
		unique_ptr<ExpNode> AsExpNode();

		/// <summary>
		/// Adds coefficients
		/// </summary>
		void AddToCoefficient(AdditiveTerm *other);

		/// <summary>
		/// Checks if two AdditiveTerm have the same base
		/// </summary>
		bool CompareBase(const AdditiveTerm &other);

		bool operator<(const AdditiveTerm &other) const {
			if (base_->IsNumericalValue()) {
				return false;
			}
			else if (other.base_->IsNumericalValue()) {
				return true;
			}
			return base_string < other.base_string;
		}

	private:
		// Used to compare bases
		string base_string;
		double coefficient_;
		unique_ptr<ExpNode> base_;
};