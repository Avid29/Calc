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
Test const tests_[2] = { Test("2+2", "4"), Test("x^2", "x^2")};

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