#include <iostream>

#include "../../src/Calculator-Lib/include/ExpNode.h"
#include "../../src/Calculator-Lib/include/Parse.h"

using namespace std;

struct Test {
    public:
        Test(string input, string output) : input_ (input), output_ (output), actual_output ("") { }

        bool Passed() {
            return output_ == actual_output;
        }

        string &GetInput() {
            return input_;
        }

        string &GetOutput() {
            return output_;
        }

        // Gets the result from running
        string &GetResult() {
            return actual_output;
        }

        // Runs test and set result
        void Run() {
            unique_ptr<ExpTree> tree;
            int result = Parse(input_, tree);
            if (result == -1) {
                actual_output = tree->Simplify()->Print();
            }
            else {
                actual_output == "error at char: " + result;
            }
        }



    private:
        string input_;
        string output_;

        string actual_output;
};

// List of all tests to run
Test const tests_[14] = 
{
    Test("2+5", "7"),
    Test("4*3", "12"),
    Test("3^4", "81"),
    Test("3(4+5)", "27"),
    Test("(4+5)", "9"),
    Test("3(4+5)(0.1)", "2.7"),
    Test("(0.1)3(4+5)", "2.7"),
    Test("x-2", "x-2"),
    Test("x^2", "x^2"),
    Test("(0)3(4x+5)", "0"),
    Test("2x*2x", "4x^2"),
    Test("3x+(5x+6x+8xy)", "14x+8xy"),
    Test("3(x+3)", "3x+9"),
    Test("(x+3)(x+3)", "x^2+6x+9"),
    //Test("(x+3)^2+(x+3)^x", "(x+3)^(x+2)")
};

int main()
{
    int failCount = 0;

    // Runs each test and compares result to accepted result
    for (Test test : tests_)
    {
        cout << "Test: " << test.GetInput() << " running" << endl;
        test.Run();
        cout << "Expected: " << test.GetOutput() << ". Got: " << test.GetResult() << endl;
        cout << "Test " << (test.Passed() ? "passed" : "failed") << endl << endl;
        if (!test.Passed())
            failCount++;
    }

    cout << failCount << " tests failed!";
}