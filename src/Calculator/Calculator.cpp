#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#include "include/Parse.h"
#include "include/ExpTree.h"

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
		unique_ptr<ExpTree> exp_tree;
		int result = Parse(str, exp_tree);
		if (exp_tree == nullptr) {
			cout << "Error occured at char " << result+1 << endl;
		}
		else {
			// Simplifies ExpTree and conver back to string
			cout << endl << exp_tree->Simplify()->Print() << endl;
		}
	}
}
