#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#include "Simplify.h"
#include "InternalParser.h"
#include "InternalPrinter.h"
#include "ExpTree.h"

using namespace std;

int main(int argc, char** argv) {
	while (true) {
		// Gets equation as string
		string str;
		cout << "Enter an Equation (q to quit): ";
		cin >> str;

		// Checks for quit
		if (str == "q") {
			cout << "Done!";
			return 0;
		}

		// Convert equation to ExpTree
		InternalParser* parser = new InternalParser();
		InternalPrinter* printer = new InternalPrinter();
		unique_ptr<ExpTree> tree;
		unique_ptr<ExpTree>* treePtr = &tree;
		Status status = Parse(str, treePtr);
		if (status.Failed()) {
			cout << printer->PrintError(status) << endl;
		}
		else {
			Simplifier* simplifier = new Simplifier();
			// Simplifies ExpTree and conver back to string
			cout << endl << tree->Execute(simplifier)->Print(*printer) << endl << endl;
			delete simplifier;
		}
		delete parser;
		delete printer;
	}
}
