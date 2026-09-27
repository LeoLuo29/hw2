// Standalone test driver for parseStringToWords (NOT part of the submission)
// Build: g++ -g -Wall -std=c++11 test_util.cpp util.cpp -o test_util
// Run:   ./test_util
#include <iostream>
#include "util.h"
using namespace std;

void show(string s) {
    set<string> words = parseStringToWords(s);
    cout << "\"" << s << "\" -> { ";
    for (set<string>::iterator it = words.begin(); it != words.end(); ++it) {
        cout << *it << " ";
    }
    cout << "}" << endl;
}

int main() {
    // Spec examples
    show("Men's Fitted Shirt");   // expect: fitted men shirt
    show("J.");                    // expect: (nothing)
    show("I'll");                  // expect: ll
    show("Data Abstraction & Problem Solving with C++");
                                   // expect: abstraction data problem solving with

    // Edge cases
    show("");                      // expect: (nothing)
    show("a b c");                 // expect: (nothing)
    show("hello");                 // expect: hello
    show("C++  --  Java");         // expect: java
    show("HeLLo WoRLD");           // expect: hello world
    show("men Men MEN");           // expect: men (set removes duplicates)
    return 0;
}
