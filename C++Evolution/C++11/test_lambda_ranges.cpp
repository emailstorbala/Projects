#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

bool isEven(int x) {
    return x%2 == 0;
}

int main() {
    vector <int> tmp = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // Uniform initialisation in C++11

    /*** Older way ***/
    if (false) {
        vector <int> res;
        for (size_t idx = 0; idx < tmp.size(); idx++) {
            if (isEven(tmp.at(idx))) res.push_back(tmp.at(idx));
        }

        cout << "Result: " << endl;
        for (size_t idx = 0; idx < res.size(); idx++) {
            cout << res.at(idx) << endl;
        }
    }

    /*** New way ***/
    auto locEven = [](int x) { return x%2 == 0; };
    vector <int> res;
    for ( auto && x : tmp) {
        if (locEven(x)) res.push_back(x);
    }

    cout << "Result: " << endl;
    for ( auto && x : res) {
        cout << x << endl;
    }
    /***/

    return EXIT_SUCCESS;
}
