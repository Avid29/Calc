#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#include "LaTeXParser.h"
#include "LaTeXPrinter.h"
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
		LaTeXParser* parser = new LaTeXParser();
		LaTeXPrinter* printer = new LaTeXPrinter();
		parser->ParseString(str);
		parser->Finalize();
		if (!parser->IsDone()) {
			// TODO:
			//parser->PrintError();
		}
		else {
			// Simplifies ExpTree and conver back to string
			cout << parser->GetTree()->Simplify()->Print(*printer) << endl;
		}
		delete parser;
		delete printer;
	}
}
