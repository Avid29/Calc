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
		void AddToExponent(MultiplicativeTerm *other, IOperation* operation);

		/// <summary>
		/// Checks if two MultiplicateTerms have the same base
		/// </summary>
		bool operator==(const MultiplicativeTerm &other) const;

		/// <summary>
		/// Compares sort order of this with with
		/// </summary>
		bool operator<(const MultiplicativeTerm &other) const;

	private:
		// Used to compare bases
		string base_string;

		unique_ptr<ExpNode> base_;
		unique_ptr<ExpNode> exponent_;
};