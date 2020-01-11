#pragma once

#include "include/ExpNode.h"

class AdditiveTerm {
	public:
		/// <summary>
		/// Finds AdditiveTerm to represent node
		/// </summary>
		AdditiveTerm(ExpNode *node);

		/// <summary>
		/// Gets Term as an ExpNode
		/// </summary>
		ExpNode *AsExpNode();

		/// <summary>
		/// Adds coefficients
		/// </summary>
		void AddToCoefficient(AdditiveTerm *other);

		/// <summary>
		/// Checks if two AdditiveTerm have the same base
		/// </summary>
		bool CompareBase(const AdditiveTerm &other);

	private:
		// Used to compare bases
		string base_string;

		double coefficient_;
		ExpNode *base_;
};