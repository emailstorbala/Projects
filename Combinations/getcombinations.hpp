#ifndef __GETCOMBINATIONS_H__
#define __GETCOMBINATIONS_H__

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <fmt/format.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <tuple>
#include <memory>
#include <boost/program_options.hpp>

using std::string;
using std::vector;

class Combinations {
    string inp;
    int totalLimit;
    vector <string> combs;
    public:
        Combinations(string _inp, int _tot);
        Combinations() = delete;
        void SetInitialCombs(vector <string> _combs) {
            this->combs = _combs;
        }
        template <typename T>
        T CreateCombinations();
        bool IsDuplicate(vector <string> itemList, string item);
};

#endif
