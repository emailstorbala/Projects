#include <iostream>
#include <fmt/format.h>

using std::cout;
using std::endl;

void f(int) {
    cout << "f(int) is called" << endl; 
}

void f(char *) {
    cout << "f(char *) is called" << endl;
}

int main() {
    //C++03
    //
    f(0); // f(int) called

    //C++11
    //
    //f(NULL); // Ambiguous call
    f(nullptr); //unambiguous, calls #2

    return EXIT_SUCCESS;
}
