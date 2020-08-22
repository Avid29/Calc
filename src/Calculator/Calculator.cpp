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

int main(int argc, char **argv) {
	while (true) {
		// Gets equation as string
		string str;
		cout << "Enter an Equation (q to quit): ";
		cin >> str;

		// Checks for 
		if (str == "q") {
			cout << "Done!";
			return 0;
		}

		// Convert equation to ExpTree
		InternalParser* parser = new InternalParser();
		InternalPrinter* printer = new InternalPrinter();
		parser->ParseString(str);
		Error error = parser->Finalize();
		if (error.Occured()) {
			cout << printer->PrintError(error) << endl;
		}
		else {
			Simplifier* simplifier = new Simplifier();
			// Simplifies ExpTree and conver back to string
			cout << endl << parser->GetTree()->Execute(simplifier)->Print(*printer) << endl << endl;
			delete simplifier;
		}
		delete parser;
		delete printer;
	}
}
