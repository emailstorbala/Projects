/* Copyright [2022-2023] Balamurugan R <emailstorbala@gmail.com> */
#include <fmt/format.h>
#include <iostream>
#include <tuple>
#include <boost/program_options.hpp>
#include "Utilities.h"

using boost::program_options::notify;
using boost::program_options::parse_command_line;
using boost::program_options::store;
using boost::program_options::variables_map;
using boost::program_options::options_description;
using boost::program_options::value;
using boost::program_options::error;

using std::cout;
using std::endl;
using std::string;
using std::tuple;
using std::vector;
using fmt::print;

tuple<string> ParseProgramArguments(const int argc, const char * argv[]) {
    string filename;
    variables_map vm;
    options_description prgDesc{"Usage"};

    try {
        prgDesc.add_options()
            ("help, h", "Help screen")
            ("i", value<string>(&filename)->required(), "Input File");

        store(parse_command_line(argc, argv, prgDesc), vm);

        if (vm.count("help") || vm.count("h")) {
            cout << prgDesc << endl;
            exit(0);
        }

        notify(vm);
    } catch (const error &ex) {
        fmt::print(stderr, "Exception: {}\n", ex.what());
        cout << prgDesc << endl;
        exit(3);
    }

    return make_tuple(filename);
}

int main(int argc, const char * argv[]) {
    auto && [fname] = ParseProgramArguments(argc, argv);
    fmt::print("Input file name provided is {}\n", fname);

    string sample = "Guduvanchery:Tamilnadu:India";
    Utilities utils;
    auto splitList = utils.Split(sample, ':');

    for (auto && tmp : splitList) {
        fmt::print("item is {}\n", tmp);
    }
    return EXIT_SUCCESS;
}
