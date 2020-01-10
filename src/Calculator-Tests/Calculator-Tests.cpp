#include <iostream>

#include "include/ExpTree.h"
#include "include/Parse.h"

using namespace std;

struct Test {
    public:
        Test(string input, string output) : input_ (input), output_ (output) { }

        string input_;
        string output_;
};

// List of all tests to run
Test const tests_[7] = 
{
    Test("2+5", "7"),
    Test("4*3", "12"),
    Test("3^4", "81"),
    Test("3(4+5)", "27"),
    Test("(4+5)", "9"),
    Test("3(4+5)(0.1)", "2.7"),
    //Test("3(x+5)(0.1)", "0.3x+1.5"),
    //Test("3(4x+2y)(0.5)", "6x+3y"),
    //Test(".5(x+2y)", ".5x+y"),
    Test("x^2", "x^2")
};

int main()
{
    // TODO: Track failed tests

    // Runs each test and compares result to accepted result
    for (Test test : tests_)
    {
        cout << "Test: " << test.input_ << " running" << endl;
        string result = Parse(test.input_)->Simplify()->Print();
        cout << "Expected: " << test.output_ << ". Got: " << result << endl;
        cout << "Test " << ((result == test.output_) ? "passed" : "failed") << endl << endl;
    }
}