#pragma once

#include "OperNode.h"

class MultiplicativeTerm {
	public:
		/// <summary>
		/// Finds MultiplicativeTerm to represent node
		/// </summary>
		/// <param name="node">root node of term to convert</param>
		MultiplicativeTerm(ExpNode *node);

		/// <summary>
		/// Gets Term as an ExpNode
		/// </summary>
		ExpNode *AsExpNode();

		/// <summary>
		/// Adds exponents
		/// </summary>
		void AddToExponent(MultiplicativeTerm *other);

		/// <summary>
		/// Checks if two MultiplicateTerms have the same base
		/// </summary>
		bool CompareBase(const MultiplicativeTerm &other);

	private:
		// Used to compare bases
		string base_string;

		ExpNode *base_;
		ExpNode *exponent_;
};