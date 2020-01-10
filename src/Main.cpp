#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#include "include/Parse.h"
#include "include/ExpTree.h"

using namespace std;

int main(int argc, char **argv) {
	// Get Equation
	while (true) {
		string str;
		cout << "Enter an Equation (q to quit): ";
		cin >> str;

		if (str == "q") {
			cout << "Done!";
			return 0;
		}

		ExpTree *exp_tree = Parse(str);
		if (exp_tree == nullptr) {
			cout << "error occured" << endl;
		}
		cout << endl << exp_tree->Simplify()->Print() << endl;
	}
}
