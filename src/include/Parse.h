#pragma once
#include <string>
#include <vector>

#include "ExpNode.h"
#include "ExpTree.h"
#include "FValueNode.h"
#include "IValueNode.h"
#include "OperNode.h"
#include "ValueNode.h"

using namespace std;

enum ParserState {
	BEGIN,
	NOPER,
	UOPER,
	INT,
	FLOAT,
	DONE
};

class ParseState {
	public:
		ParseState();
		int ParseString(string equation);
		bool ParseNextChar(char c);

		void Finalize();
		ExpTree *GetTree();
		ExpTree *FinalizeAndReturn();

	private:
		bool ParseBegin(char c);
		bool ParseNOper(char c);
		bool ParseUOper(char c);
		bool ParseInt(char c);
		bool ParseFloat(char c);

		void DepositIntCache();
		void DepositFloatCache();

		ParserState state_;
		ExpTree *tree_;
		string cache_;
};

ExpTree *Parse(string equation);
