#pragma once

#include "ExpNode.h"

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
		bool operator==(const AdditiveTerm &other);

		/// <summary>
		/// Compares sort order of this with with
		/// </summary>
		bool operator<(const AdditiveTerm &other) const;

	private:
		// Used to compare bases
		string base_string;
		double coefficient_;
		unique_ptr<ExpNode> base_;
};