#include <iostream>
#include <fmt/format.h>

using std::cout;
using std::endl;
using fmt::format;

int main() {
    float loc1 = 4.2f;
    auto  loc2 = 4.2f;

    if (typeid(loc1).name() == typeid(loc2).name()) {
        cout << "Both loc1 and loc2 are same datatype!" << endl;
    }

    return EXIT_SUCCESS;
}
