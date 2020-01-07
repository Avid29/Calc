#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#include "include/Parse.h"
#include "include/ExpTree.h"

using namespace std;

int main(int argc, char **argv) {
	// Get Equation
	string str;
	cout << "Enter an Equation: ";
	cin >> str;

	ExpTree *exp_tree = Parse(str);
	cout << endl << exp_tree->Print() << endl;
}
