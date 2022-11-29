#include <iostream>
#include <fmt/format.h>

using std::cout;
using std::endl;
using fmt::format;

int main() {
    std::string s1 = "Hello";
    std::string s2 = "World";

    //std::string s3 = s1 + s2; // Using r-value reference
    std::string s3 = s1 + s2;

    cout << format("Value of s3 is {}", s3) << endl;
    return EXIT_SUCCESS;
}
